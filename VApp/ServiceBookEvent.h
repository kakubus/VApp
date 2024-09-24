#pragma once
#include "Globals.h"
#include "CarEvent.h"
#include <ctime>

class CarEvent;

class ServiceBookEvent
{
public:
	ServiceBookEvent(time_t timestamp, unsigned int mileage, CarEvent* carEvent);
	~ServiceBookEvent();

	void addEvent(time_t timestamp, unsigned int mileage, CarEvent* carEvent);
	void deleteEvent();

	static const char* sqlTable();

private:
	time_t _timestamp;
	unsigned int _mileage_stamp;
	CarEvent* _carEvent;
};

