#include <QCoreApplication>
#include "sqlworker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.
    qDebug() << "Run - SQL Test application\n";

    SQLWorker* sqlwrk = new SQLWorker();
    // sqlwrk->init(Db_Type::MYSQL, "admin", "admin", "192.168.2.10", "Test");
    sqlwrk->init(Db_Type::SQLITE, "db_file.db");

    QString createTableQuery = "CREATE TABLE IF NOT EXISTS Vehicle (id SERIAL PRIMARY KEY, mark VARCHAR(255) NOT NULL, model VARCHAR(255) NOT NULL, VIN VARCHAR(255) NOT NULL UNIQUE, year INT NOT NULL, carBookId INT, FOREIGN KEY (carBookId) REFERENCES CarBook(id));";
    sqlwrk->execute(createTableQuery);
    sqlwrk->countFromTable("Vehicle");

    createTableQuery = "INSERT INTO Vehicle (mark, model, VIN, year, carBookId) VALUES ('VW', 'Golf', 'JTDBR32E530050021', 2021, 1);";
    sqlwrk->execute(createTableQuery);
    sqlwrk->countFromTable("Vehicle");

    createTableQuery = "INSERT INTO Vehicle (mark, model, VIN, year, carBookId) VALUES ('VW', 'Golf', 'JTDBR32E530050021', 2021, 1);";
    sqlwrk->execute(createTableQuery);

    createTableQuery = "SELECT * FROM Vehicle;";
    auto experiment = sqlwrk->execute(createTableQuery);

  //  return 0;
    return a.exec();

}
