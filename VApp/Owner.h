#pragma once
#include "Globals.h"
#include "Vehicle.h"
#include "CarCosts.h"

#include <string>
#include <vector>

class Vehicle;
class CarCosts;

class Owner
{
public:
	Owner(std::string nick, unsigned short age);
	~Owner();

	void addVehicle();
	void removeVehicle();

	static const char* sqlTable();

private:
	std::string _nick;
	unsigned short _age;
	std::vector<Vehicle*> _VehicleID;
	std::vector<CarCosts*> _costsID;

};

