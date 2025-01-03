#include "sqlworker.h"

SQLWorker::SQLWorker(QObject *parent)
    : QObject{parent}
{}

SQLWorker::SQLWorker(Db_Type database_type){
    _connected = false;
    if(Db_Type::SQLITE == database_type){
        qDebug() << Q_FUNC_INFO << "SQLITE db selected. Simply constructor called.";

    }

} // for SQLite db.
SQLWorker::SQLWorker(Db_Type database_type, QString login, QString pass, QString host, QString db_name){
    _connected = false;
    if(Db_Type::MYSQL == database_type){
        qDebug() << Q_FUNC_INFO << "MYSQL db selected. Enchanced constructor called.";

    }
} // For SQL remote servers

SQLWorker::~SQLWorker(){

}
