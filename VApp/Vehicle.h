#pragma once

#include "Globals.h"
#include "ServiceBook.h"
#include "CarCosts.h"
#include "Owner.h"

#include <string>
#include <vector>

class ServiceBook;
class CarCosts;
class Owner;

enum EngineType
{
	Petrol, Diesel, Electric, Hybrid
};


class Vehicle
{
public:
	Vehicle(std::string VIN, std::string mark, std::string model, int year, std::string colour, unsigned int mileage, EngineType engineType, std::string engineCode, int enginePower, std::string description);
	~Vehicle();

	static const char* sqlTable();

protected:

private:
	std::string _VIN;
	std::string _mark;
	std::string _model;
	int _year;

	std::string _colour;
	unsigned int _mileage;

	EngineType _engineType;
	std::string _engineCode;
	int _enginePower;

	std::string _description;

	std::vector<int> _vehiclePhotos;

	Owner* _OwnerID;
	ServiceBook* _ServiceBookID;
	CarCosts* _CarCostsID;
};

/// <summary>
/// Very important SQL query!
/// </summary>
/// 


