#include "Database.h"
#include <iostream>
#include <strstream>


Database::Database(const char* name) : db_name(name) {
    size_t name_length = sizeof(*name) / sizeof(char);
    errorMsg = nullptr;

    if ((name_length < 0)) {

        db_name = "default.db";
    }
    else {
        db_name = name;
    }

    int errorCode = sqlite3_open(db_name, &db);

    if (errorCode) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Opened database" << std::endl;

        dbObjectInit(Vehicle::sqlTable());
        dbObjectInit(Owner::sqlTable());

    }

    this->errorCode = errorCode;
    //errorMsg = sqlite3_errmsg(db);
}

Database::~Database()
{
    sqlite3_close(db);
}

ErrorLog Database::execute(const char* command)
{
    this->errorMsg = "OK";
    char* err;
    
    auto errorCode = sqlite3_exec(db, command, NULL, NULL, &err);
    this->errorMsg = err;
    if (errorCode != SQLITE_OK) {
        std::strstream msg;
        msg << "Cannot do this operation: " << sqlite3_errmsg(db);
        this->errorMsg = msg.str();
        std::cout << msg.str();
    }



    return ErrorLog(errorCode, this->errorMsg);
}

ErrorLog Database::openDbFromFile(std::string filename)
{
    int errorCode = sqlite3_open("firstDb.db", &db);
    const char* str_msg = "OK";

    if (errorCode) {
        std::strstream msg;
        msg << "Can't open database: " << sqlite3_errmsg(db);
        str_msg = msg.str();
    }

    return ErrorLog(errorCode, str_msg);
}

ErrorLog Database::dbObjectInit(const char* sqlTable)
{
    this->errorMsg = "OK";
    this->errorCode = 0;
    
    std::cout << "Initialize database tables...\n";

    auto result = execute(sqlTable);
    if (result.errorCode != SQLITE_OK) {
        std::strstream msg;
        msg << "Cannot do this operation: " << sqlite3_errmsg(db);
        this->errorMsg = msg.str();

        std::cout << msg.str();
    }

    return ErrorLog(errorCode, errorMsg);
}
