#pragma once
#include <set>
#include "Worker.h"
#include <BWAPI.h>


class Base
{
public:
	Base(BWAPI::TilePosition location);
	~Base();

	BWAPI::TilePosition  getBaseLocation();
	BWAPI::Unit getHatch() ;
	std::set<BWAPI::Unit>*  getRefineries();
	std::set<BWAPI::Unit>*  getGeysers();
	std::set<BWAPI::Unit>*  getMinerals();

	std::vector<Worker*>  getWorkers();

	std::vector<Worker*>  assignedWorker;
	int nbWorkerOnGas = 0;

	//std::map<BWAPI::Unit*, std::vector<Worker*>> refineriesAndWorker;
	//std::map<BWAPI::Unit*, std::vector<Worker*>>  mineralsAndWorker;
	//std::set<BWAPI::Unit*>  geysers;

	void setHatch(BWAPI::Unit unit);
	void setGeysers(std::set<BWAPI::Unit>  geysers);
	void setActiveHatch(bool active);
	void setActiveGas(bool active);
	void setActiveMinerals(bool active);

	bool isActiveHatch(){ return this->activeHatch; };
	bool isActiveMinerals(){ return this->activeMinerals; };
	bool isActiveGase(){ return this->activeGas; };
	bool isBeingConstructed(){ return this->beingConstructed; };


	BWAPI::TilePosition  baseLocation;
	BWAPI::Unit hatch = NULL;
	BWAPI::Unit refinery = NULL;

	//std::set<BWAPI::Unit*>  refineries;
	//std::set<BWAPI::Unit*> minerals;

	bool activeHatch = false;
	bool activeMinerals = false;
	bool activeGas = false;
	bool beingConstructed = true;
	bool hasBeenInitialise = false;

private:


};

