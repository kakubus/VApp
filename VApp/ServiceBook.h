#pragma once
#include "ServiceBookEvent.h"
#include <vector>

class ServiceBookEvent;

class ServiceBook
{
public:
	ServiceBook();
	~ServiceBook();

	void newServiceEvent();
	void deleteServiceEvent();
	void modifyServiceEvent();

	static const char* sqlTable();

protected:


private:
	unsigned int _serviceBookId;
	std::vector<ServiceBookEvent*> _serviceBookRows;
};

