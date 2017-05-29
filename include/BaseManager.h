#pragma once
#include <BWAPI.h>
#include "Base.h"
#include <BWAPI.h>

class BaseManager : public BWAPI::AIModule
{
public:
	BaseManager();
	~BaseManager();

	int missingDrone = 2;
	int missingRefineries = 0;
	int workerPerBase = 18;

	void updateMissingDrones();
	BWAPI::TilePosition playerStartLocation;
	BWAPI::TilePosition nextBaseLocation;

	void BaseManager::freeAWorker(Worker *worker);
	Worker *getFreeWorker();
	Worker *getBuilderWorker();
	Base *getBaseWhoCanMorph(BWAPI::UnitType type);

	BWAPI::TilePosition getNewBaseLocation();
	void updateNextBaseLocation();

	void putSomeWorkerToRefinery(Base* base);


	virtual void onStart() ;
	virtual void onEnd(bool isWinner) ;
	virtual void onFrame() ;
	virtual void onSendText(std::string text) ;
	virtual void onReceiveText(BWAPI::Player player, std::string text) ;
	virtual void onPlayerLeft(BWAPI::Player player) ;
	virtual void onNukeDetect(BWAPI::Position target) ;
	virtual void onUnitDiscover(BWAPI::Unit unit) ;
	virtual void onUnitEvade(BWAPI::Unit unit) ;
	virtual void onUnitShow(BWAPI::Unit unit) ;
	virtual void onUnitHide(BWAPI::Unit unit) ;
	virtual void onUnitCreate(BWAPI::Unit unit) ;
	virtual void onUnitDestroy(BWAPI::Unit unit) ;
	virtual void onUnitMorph(BWAPI::Unit unit) ;
	virtual void onUnitRenegade(BWAPI::Unit unit) ;
	virtual void onSaveGame(std::string gameName) ;
	virtual void onUnitComplete(BWAPI::Unit unit) ;

	void BaseManager::addBase(BWAPI::TilePosition  location, bool isEco);
	void BaseManager::removeBase(BWAPI::Unit unit);
	void BaseManager::createBase(BWAPI::Unit unit);
	Base* BaseManager::getBase(BWAPI::TilePosition  location);
	void BaseManager::expand();

	void BaseManager::removeWorker(BWAPI::Unit unit);
	void BaseManager::createWorker(BWAPI::Unit unit);

	std::set<Base*>	allEcoBases;
	std::set<Base*>	allBases;
	std::set<Worker*>	allWorkers;
	std::set<Worker*>	allFreeWorker;
	std::set<Worker*>	allWorkingWorker;

private:

	void updateBasesState();
	void updateWorkesState();

	void processGather();

	void balanceWorkers();

};



