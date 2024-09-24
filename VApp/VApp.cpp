// VApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "sqlite3.h"

#include "Database.h"

int main()
{
    /*
    sqlite3* db;
    char* errorMsg = 0;
    int errorCode = sqlite3_open("firstDb.db", &db);

    if (errorCode) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    }
    else {
        std::cout << "Opened database" << std::endl;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS VEHICLE("
        "id INT PRIMARY KEY     NOT NULL,"
        "vin            VARCHAR(30)     ,"
        "mark           TEXT    NOT NULL,"
        "model          TEXT    NOT NULL,"
        "year           INT     NOT NULL,"
        "engineType     TEXT            ,"
        "enginePower    INT             ,"
        "mileage        INT(10)          "
        ");";

    errorCode = sqlite3_exec(db, sql, NULL, NULL, &errorMsg);
    if (errorCode != SQLITE_OK) {
        std::cout << "Problem with DB sql" << std::endl;
        std::cout << stderr << errorMsg << std::endl;
    }
 sqlite3_close(db);
    */


    Database* baza = new Database("default.db");
    baza->execute("INSERT INTO VEHICLE VALUES(' ', 'WVWZZZ1234567890', 'VW', 'Golf', 2000, 'Gasoline', 'ATN', '75kW', '205432', '', '1', '1', '1');");


   // baza.execute(sql);

   
}