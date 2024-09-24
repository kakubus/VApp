#pragma once
#include "Globals.h"
#include "ServiceBook.h"
#include <strstream>

class ServiceBook;

enum CarEventType
{
	CarCrash, Failure, Service, Exploitation, Modification	
};

class CarEvent
{
public:
	CarEvent();
	~CarEvent();

	float cost;
	std::strstream describtion; // maybe XML?

	static const char* sqlTable();

private:
	unsigned int _CarEventID;
	CarEventType _CarEventType;
	ServiceBook* _ServiceBookID;

	
};

