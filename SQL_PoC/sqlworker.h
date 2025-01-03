#ifndef SQLWORKER_H
#define SQLWORKER_H

#include <QObject>

#include <QSqlError>
#include <QSqlDatabase>
#include <QSql>


enum Db_Type{SQLITE, MYSQL};

class SQLWorker : public QObject
{
    Q_OBJECT
public:
    explicit SQLWorker(QObject *parent = nullptr);
    SQLWorker(Db_Type database_type); // for SQLite db.
    SQLWorker(Db_Type database_type, QString login, QString pass, QString host, QString db_name); // For SQL remote servers

    ~SQLWorker();

    void createTable();

    void saveElement();
    void getElement();
    void findElement();

    bool isConnected();

private:
    QSqlDatabase _db;
    bool _connected;



signals:
};

#endif // SQLWORKER_H
