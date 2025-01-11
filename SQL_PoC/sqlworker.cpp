#include "sqlworker.h"

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
        qDebug() << Q_FUNC_INFO << "ERROR Query: " << _db.lastError().text();
        return QSqlRecord();
    }
    if(query.next()){
        return query.record();
    }
    return QSqlRecord();
}



