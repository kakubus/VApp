#include "Vehicle.h"

const char* Vehicle::sqlTable()
{
	return "CREATE TABLE IF NOT EXISTS VEHICLE("
		"id INT PRIMARY KEY			NOT NULL,"
		"vin            VARCHAR(30)			,"
		"mark           TEXT		NOT NULL,"
		"model          TEXT		NOT NULL,"
		"year           INT			NOT NULL,"
		"engineType     INT(2)				,"
		"engineCode     VARCHAR(5)			,"
		"enginePower    INT					,"
		"mileage        INT(10)				,"
		"description    VARCHAR(64)			,"
		"ownerID		INT					,"
		"serviceBookID  INT					,"
		"carCostsID		INT					"/*,"
		"FOREIGN KEY	(ownerID)			,"
		"FOREIGN KEY	(serviceBookID)		,"
		"FOREIGN KEY	(carCostsID)		 "*/
	");";;
}
