#include "sqlworker.h"

SQLWorker::SQLWorker(QObject *parent)
    : QObject{parent}
{}

SQLWorker::SQLWorker(Db_Type database_type){

} // for SQLite db.
SQLWorker::SQLWorker(Db_Type database_type, QString login, QString pass, QString host, QString db_name){

} // For SQL remote servers

SQLWorker::~SQLWorker(){

}
