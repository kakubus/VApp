#include "Owner.h"

Owner::Owner(std::string nick, unsigned short age)
{
	_nick = nick;
	_age = (age > 0) ? age : 18;
}

const char* Owner::sqlTable()
{
	return "CREATE TABLE IF NOT EXISTS OWNER("
		"id INT PRIMARY KEY			NOT NULL,"
		"name            VARCHAR(30)			,"
		"age           TEXT		NOT NULL		,"
		"description    VARCHAR(64)				,"
		"vehicleID		INT						,"
		"carCostsID		INT					"/*,"
		"FOREIGN KEY	(ownerID)			,"
		"FOREIGN KEY	(serviceBookID)		,"
		"FOREIGN KEY	(carCostsID)		 "*/
		");";;
}
