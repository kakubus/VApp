#pragma once
#include "Vehicle.h"
#include "ServiceBook.h"

class Vehicle;
class ServiceBook;

class CarCosts
{
public:
	float getPurchasePrice();
	float getSetPrice();

	void set(float purchasePrice, float sellPrice);
	
	double calculateExploitationCosts();
	double calculateTotalCosts();

	static const char* sqlTable();

private:
	float _purchasePrice;			/// Purchase costs
	float _sellPrice;				/// Sell price
	float _totalCosts;				/// Exploitation costs

	ServiceBook* _ServiceBookID;	/// Identifier of service book
	Vehicle* _VehicleID;			/// Identifier of vehicle
	
};

