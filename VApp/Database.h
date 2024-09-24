#include "Globals.h"
#include <stdio.h>
#include <conio.h>
#include <string>
#include "sqlite3.h"

#include "Owner.h"
#include "CarCosts.h"
#include "CarEvent.h"
#include "ServiceBook.h"
#include "ServiceBookEvent.h"

struct ErrorLog {
	int errorCode = 0;
	const char* errorMsg;

	ErrorLog(int errorCode, const char* errorMsg) {
		this->errorCode = errorCode;
		this->errorMsg = errorMsg;
	}
};

class Database
{
	//Could be useful friendship
	friend class Owner;
	friend class CarCosts;
	friend class CarEvent;
	friend class ServiceBook;
	friend class ServiceBookEvent;

public:
	Database(const char* name);
	~Database();
	ErrorLog execute(const char* command);
	Database* get();
	ErrorLog openDbFromFile(std::string filename);


private:
	const char* & db_name;
	sqlite3* db;
	const char* errorMsg;
	int errorCode;

	ErrorLog dbObjectInit(const char* sqlTable);
};
