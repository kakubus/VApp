#include "sqlworker.h"
#include <algorithm>

SQLWorker::SQLWorker(QObject *parent)
    : QObject{parent}
{
    qDebug() << Q_FUNC_INFO << "Constructor called. Available drivers: " << QSqlDatabase::drivers();
}

SQLWorker::SQLWorker(Db_Type database_type){
    if(_db.isOpen())
        _db.close();
    _connected = false;
    qDebug() << Q_FUNC_INFO << "Constructor called. Available drivers: " << QSqlDatabase::drivers();
}

SQLWorker::~SQLWorker(){
    if (_db.isOpen())
        _db.close();
    qDebug() << Q_FUNC_INFO << "Destructor called. Destroy object, disconnecting database.";
}

bool SQLWorker::init(Db_Type database_type, QString login, QString pass, QString host, QString db_name){
    _connected = false;
    if(Db_Type::MYSQL == database_type){
        qDebug() << Q_FUNC_INFO << "MYSQL db selected. Enchanced constructor called.";
        _db_type = Db_Type::MYSQL;

        _db = QSqlDatabase();
        _db = QSqlDatabase::addDatabase("QMYSQL","sqlworker_db_instance");
        _db.setHostName(host);
        _db.setDatabaseName(db_name);
        _db.setUserName(login);
        _db.setPassword(pass);

        _connected = _db.open();
        if(!_connected){
            qDebug() << Q_FUNC_INFO << "ERROR: " << _db.lastError().driverText();
            return false;
        }
        else{
            qDebug() << Q_FUNC_INFO << "MySQL db (db_name: "<< db_name <<") opened successfully.";
            return true;
        }
    }
    else{
        qDebug() << Q_FUNC_INFO << "ERROR: " << "Not recognized db type. Wrong type provided.";
        return false;
    }
}

bool SQLWorker::init(Db_Type database_type, QString db_name){
    _connected = false;
    if(Db_Type::SQLITE == database_type){
        qDebug() << Q_FUNC_INFO << "SQLITE db selected. Simply constructor called.";
        _db_type = Db_Type::SQLITE;

        _db = QSqlDatabase::addDatabase("QSQLITE");
        _db.setDatabaseName(db_name);

        _connected = _db.open();
        if(!_connected){
            qDebug() << Q_FUNC_INFO << "ERROR: " << _db.lastError().driverText();
            return false;
        }
        else{
            qDebug() << Q_FUNC_INFO << "SQLITE db (db_name: "<< db_name <<") opened successfully.";
            checkIfEmptyDb();
            return true;
        }
    }
    else{
        qDebug() << Q_FUNC_INFO << "ERROR: " << "Not recognized db type. Wrong type provided.";
        return false;
    }
}

bool SQLWorker::checkIfEmptyDb(){
    if(!_db.isOpen()){
        qDebug() << Q_FUNC_INFO << "ERROR: " << "Database is not opened.";
        return true;
    }

    QSqlQuery query(this->_db);

    // if(_db_type == Db_Type::MYSQL){

    // }
    // if(_db_type == Db_Type::SQLITE){

    // }
    query.prepare("SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%';");

    if(!query.exec()){
        qDebug() << Q_FUNC_INFO << "ERROR Query: " << _db.lastError().text();
        return true;
    }

    if(query.next()){ // If it is true, it means that there are tables inside.
        qDebug() << Q_FUNC_INFO << "Database is not empty!";
        return false;
    }
    qDebug() << Q_FUNC_INFO << "Database is empty!";
    return true;
}

QSqlRecord SQLWorker::execute(QString query_to_execute){
    if(!_db.isOpen()){
        qDebug() << Q_FUNC_INFO << "ERROR: " << "Database is not opened.";
        return QSqlRecord();
    }

    QSqlQuery query(this->_db);
    query.prepare(query_to_execute);

    if(!query.exec()){
        qDebug() << Q_FUNC_INFO << "returned:" << query.lastError().text() << "ERROR Query("<< query_to_execute <<")";
        return QSqlRecord();
    }
    if(query.next()){ // if found elements
        return query.record();
    }
    return QSqlRecord();
}

QVector<QSqlRecord> SQLWorker::selectMultiplyRecords(QString query_to_execute){
    QVector<QSqlRecord> results;
    if(!_db.isOpen()){
        qDebug() << Q_FUNC_INFO << "ERROR: " << "Database is not opened.";
        return QVector<QSqlRecord>();
    }

    QSqlQuery query(this->_db);
    query.prepare(query_to_execute);

    if(!query.exec()){
        qDebug() << Q_FUNC_INFO << "ERROR Query: " << _db.lastError().text();
        return QVector<QSqlRecord>();
    }
    while(query.next()){ // How will this behave when I would add multithreading?
        results.push_back(query.record());
    //      query.record().value(1);
    //      auto dupa = query.record().value(2);

    }

    qDebug() << Q_FUNC_INFO << "Fetched items: " << results.size() << "\n";
    return results;
}

int SQLWorker::countFromTable(QString tableName){
    QString preQuery = "SELECT COUNT (*) FROM " + tableName + "";
    int numberOfElements = 0;

    QSqlQuery query(this->_db);
    query.prepare(preQuery);

    if(!query.exec()){
        qDebug() << Q_FUNC_INFO << "ERROR Query(" << preQuery << "): " << _db.lastError().text();
        return -1;
    }
    if(query.first())
        numberOfElements = query.value(0).toInt();
    qDebug() << Q_FUNC_INFO << "Query: " << preQuery << " returned rows count: " << numberOfElements << "";

    return numberOfElements;
}

QList<QString> SQLWorker::getListTables(){
    QList<QString> listTables;
    if(!_db.isOpen()){
        qDebug() << Q_FUNC_INFO << "ERROR: " << "Database is not opened.";
        return QList<QString>();
    }

    auto list = _db.tables(QSql::Tables);
    if(list.size()== 0){
        qDebug() << Q_FUNC_INFO << "Not found any tables!";
        return QList<QString>();
    }
    for(auto element : list){
        qDebug() << Q_FUNC_INFO << "Found table named: " << element;
        listTables.push_back(element);
    }
    return listTables;
}

QList<QString> SQLWorker::getTableHeader(QString tablename){
    QList<QString> listColumnNames;
    if(!_db.isOpen()){
        qDebug() << Q_FUNC_INFO << "ERROR: " << "Database is not opened.";
        return QList<QString>();
    }
    QSqlRecord header = _db.record(tablename);
    int number_of_columns = header.count();
    if(number_of_columns == 0){
        qDebug() << Q_FUNC_INFO << "ERROR: " << "Something went wrong. Table is not exist?";
        return QList<QString>();
    }
    for(int i = 0; i < number_of_columns; i++){
        QString columnName = header.fieldName(i);
        listColumnNames.push_back(columnName);
        qDebug() << Q_FUNC_INFO << "Found column named: " << columnName;
    }
    return listColumnNames;
}

bool SQLWorker::compareTables(QString tableName, QList<QString> expectedTableHeader){
    bool result = false;
    auto sqlTableHeader = getTableHeader(tableName);

    result = std::equal(expectedTableHeader.begin(), expectedTableHeader.end(), sqlTableHeader.begin(), [](const QString &a, const QString &b){return a == b;});

    if(!result)
        qDebug() << Q_FUNC_INFO << " = "<< result << " | ERROR: Table is not valid with expected header!";
    else
        qDebug() << Q_FUNC_INFO << " = "<< result << " | Table "<< tableName << " matched properly with expected header" << expectedTableHeader;

    return result;
}

