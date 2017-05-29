#pragma once

#include "Worker.h"
//#include "Base.h"
#include <BWAPI.h>
#include <BWAPI/Order.h>

class Base;

class Worker
{
public:
	Worker();
	~Worker();

	void setWorker(BWAPI::Unit unit);
	
	BWAPI::Unit worker;
	Base *assignedBase;
	BWAPI::Order currentOrder;
	BWAPI::Unit getWorker(){ return worker;};


};

