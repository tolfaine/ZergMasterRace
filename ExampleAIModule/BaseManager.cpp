#include "BaseManager.h"

using namespace BWAPI;
using namespace Filter;

BaseManager::BaseManager()
{
}

BaseManager::~BaseManager()
{
}
void BaseManager::updateMissingDrones(){

	int missingW = 0;

	for (std::set<Base*>::iterator base = allBases.begin(); base != allBases.end(); ++base)
	{
		missingW += (workerPerBase - 3 - (*base)->assignedWorker.size());

		if ((*base)->refinery == NULL)
			missingRefineries++;
		
	}

	missingDrone = missingW;
}


void BaseManager::onStart()
{
	//BWTA::BaseLocation *playerStartLocation = BWTA::getStartLocation(BWAPI::Broodwar->self());

	//std::set<BWTA::BaseLocation*> allLocation = BWTA::getBaseLocations();

	for (BWAPI::TilePosition tp : Broodwar->getStartLocations()){

		for (auto &e : BWAPI::Broodwar->getUnitsOnTile(tp))
		{
			BWAPI::Unit unit = e;

			if (unit->getType().isResourceDepot()){
				playerStartLocation = tp;
				addBase(tp, false);
			}
		}
	}

	for (auto &u : Broodwar->self()->getUnits())
	{

		if (u->getType().isWorker()){
			createWorker(u);
		}
	}

	/*
	for (const auto& baseLocation : BWTA::getBaseLocations()) {
		BWAPI::Broodwar->sendText("Test2");
		BWAPI::TilePosition tile = baseLocation->getTilePosition();

		for (auto &e : BWAPI::Broodwar->getUnitsOnTile(tile))
		{
			BWAPI::Unit unit = e;

			if (unit->getType().isResourceDepot()){
				playerStartLocation = baseLocation;
				addBase(playerStartLocation);
			}
		}
	}
	*/
	/*
	for (std::set<BWTA::BaseLocation*>::const_iterator bl = allLocation.begin(); bl != allLocation.end(); ++bl)
	{
		BWAPI::Broodwar->sendText("Test");
		BWAPI::TilePosition tile = (*bl)->getTilePosition();

		for (auto &e : BWAPI::Broodwar->getUnitsOnTile(tile))
		{
			BWAPI::Unit unit = e;

			if (unit->getType().isResourceDepot()){
				playerStartLocation = *bl;
				addBase(playerStartLocation);
			}
		}
	}
	*/
}


void BaseManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void BaseManager::updateBasesState(){
	int nbBase = 0;

	for (std::set<Base*>::iterator base = allBases.begin(); base != allBases.end(); ++base)
	{
		nbBase++;
	//	Broodwar->sendText("Location =");

		
		Base *b = (*base);
		
		if (b->hasBeenInitialise == false || (*base)->hatch == NULL){
			b->hasBeenInitialise = true;

			BWAPI::TilePosition tile = b->getBaseLocation();
			BWAPI::Unitset unitSet = BWAPI::Broodwar->getUnitsOnTile(tile.x, tile.y);


			
			for (auto &e : unitSet){
				BWAPI::Unit unit = e;

				if (unit->getPlayer() == BWAPI::Broodwar->self() && unit->getType().isResourceDepot()){
					b->setHatch(unit);
				}
			}
			
		}
		
		if ((*base)->refinery == NULL){
			BWAPI::Unit ref = (*base)->hatch->getClosestUnit(IsRefinery, 200);
			if (ref != NULL && ref->isCompleted()){
				(*base)->refinery = ref;
				this->putSomeWorkerToRefinery(*base);
			}
		}

/*
else{

if (!hatch->isCompleted()){
b->setActiveHatch(false);
}
else{
b->setActiveHatch(true);
b->setActiveMinerals(false);
}
}
*/
	}

	for (std::set<Base*>::iterator base = allEcoBases.begin(); base != allEcoBases.end(); ++base)
	{

		Base *b = (*base);

		if (b->hasBeenInitialise == false || (*base)->hatch == NULL){
			b->hasBeenInitialise = true;

			BWAPI::TilePosition tile = b->getBaseLocation();
			BWAPI::Unitset unitSet = BWAPI::Broodwar->getUnitsOnTile(tile.x, tile.y);


			for (auto &e : unitSet){
				BWAPI::Unit unit = e;

				if (unit->getPlayer() == BWAPI::Broodwar->self() && unit->getType().isResourceDepot()){
					b->setHatch(unit);
				}
			}

		}

	}
}

void BaseManager::putSomeWorkerToRefinery(Base* base){

	for (std::vector<Worker*> ::iterator worker = base->assignedWorker.begin(); worker != base->assignedWorker.end(); ++worker){

		BWAPI::Unit workerUnit = (*worker)->getWorker();


		if (workerUnit->isCarryingGas() || workerUnit->isCarryingMinerals())
		{
			workerUnit->returnCargo();
		}
		else if (!workerUnit->getPowerUp())
		{
			BWAPI::Unit hatch = base->getHatch();
			BWAPI::Unit ref = hatch->getClosestUnit(IsRefinery);

			if (base->nbWorkerOnGas < 3){
				base->nbWorkerOnGas++;
				workerUnit->gather(base->refinery);
			}
			else{
				workerUnit->gather(hatch->getClosestUnit(IsMineralField));
			}
		}
	}

}

void BaseManager::updateWorkesState(){

}
Base * BaseManager::getBaseWhoCanMorph(BWAPI::UnitType type){

	if (type == BWAPI::UnitTypes::Zerg_Lair){
		for (std::set<Base*>::iterator base = allBases.begin(); base != allBases.end(); ++base)
		{
			if ((*base)->getHatch() != NULL){
				if ((*base)->getHatch()->getType() == BWAPI::UnitTypes::Zerg_Hatchery)
					return *base;
			}

		}
		for (std::set<Base*>::iterator base = allEcoBases.begin(); base != allEcoBases.end(); ++base)
		{
			if ((*base)->getHatch() != NULL){
				if ((*base)->getHatch()->getType() == BWAPI::UnitTypes::Zerg_Hatchery)
					return *base;
			}

		}
	}

	if (type == BWAPI::UnitTypes::Zerg_Hive){
		for (std::set<Base*>::iterator base = allBases.begin(); base != allBases.end(); ++base)
		{
			if ((*base)->getHatch() != NULL){
				if ((*base)->getHatch()->getType() == BWAPI::UnitTypes::Zerg_Lair)
					return *base;
			}

		}
		for (std::set<Base*>::iterator base = allEcoBases.begin(); base != allEcoBases.end(); ++base)
		{
			if ((*base)->getHatch() != NULL){
				if ((*base)->getHatch()->getType() == BWAPI::UnitTypes::Zerg_Lair)
					return *base;
			}


		}
	}

	for (std::set<Base*>::iterator base = allBases.begin(); base != allBases.end(); ++base)
	{
		if ((*base)->getHatch() != NULL){

			if ((*base)->getHatch()->canMorph(type) && (*base)->getHatch()->getLarva().size() >0)
				return *base;
		}

	}

	for (std::set<Base*>::iterator base = allEcoBases.begin(); base != allEcoBases.end(); ++base)
	{
		if ((*base)->getHatch() != NULL){

			if ((*base)->getHatch()->canMorph(type) && (*base)->getHatch()->getLarva().size() >0)
				return *base;
		}
		

	}
	return NULL;
}

void BaseManager::processGather(){

	for (std::set<Base*>::const_iterator base = allBases.begin(); base != allBases.end(); ++base)
	{
		int comptWorker = 0;
		for (std::vector<Worker*> ::iterator worker = (*base)->assignedWorker.begin(); worker != (*base)->assignedWorker.end(); ++worker){

			int nbGas = 0;


			BWAPI::Unit workerUnit = (*worker)->getWorker();

			if (workerUnit->isIdle())
			{

				if (workerUnit->isCarryingGas() || workerUnit->isCarryingMinerals())
				{
					workerUnit->returnCargo();
				}
				else if (!workerUnit->getPowerUp())
				{
					BWAPI::Unit hatch = (*base)->getHatch();
					BWAPI::Unit ref = hatch->getClosestUnit(IsRefinery);

					if ((*base)->refinery != NULL && (*base)->nbWorkerOnGas < 3){
						(*base)->nbWorkerOnGas++;
						workerUnit->gather((*base)->refinery);
					}
					else{
						workerUnit->gather(hatch->getClosestUnit(IsMineralField));
					}
				}
			}
			comptWorker++;
		}

	}
}

void BaseManager::balanceWorkers(){
	for (std::set<Base*>::const_iterator base = allBases.begin(); base != allBases.end(); ++base)
	{
		std::vector<Worker*> workers = (*base)->assignedWorker;

		if (workers.size() < workerPerBase){
			
			Worker *w = getFreeWorker();
			if (w != NULL){
				(*base)->assignedWorker.push_back(w);
			}
		}
	}
}


void BaseManager::onFrame()
{

	updateBasesState();
	updateWorkesState();
	updateMissingDrones();
	balanceWorkers();
	processGather();

	/*
	for (std::set<Base*>::const_iterator base = allBases.begin(); base != allBases.end(); ++base)
	{
		BWAPI::Unit *hatch = (*base)->getHatch();
		if (!(*hatch)->exists())
			removeBase(*hatch);
	}
	*/

}

void findNewBase(){
	/*for (std::set<BWTA::BaseLocation*>::const_iterator baseLocation = BWTA::getBaseLocations().begin(); baseLocation != BWTA::getBaseLocations().end(); ++baseLocation)
	{
		bool basefound = false;
		for (std::set<Base*>::const_iterator base = allBases.begin(); base != allBases.end(); ++base)
		{
			if ((*base)->getBaseLocation() == *baseLocation)
				basefound = true;
		}

		if (!basefound){
			addBase(*baseLocation);
		}

	}*/

}

void BaseManager::onSendText(std::string text){}

void BaseManager::onReceiveText(BWAPI::Player player, std::string text){}

void BaseManager::onPlayerLeft(BWAPI::Player player){}

void BaseManager::onNukeDetect(BWAPI::Position target){}

void BaseManager::onUnitDiscover(BWAPI::Unit unit){}

void BaseManager::onUnitEvade(BWAPI::Unit unit){}

void BaseManager::onUnitShow(BWAPI::Unit unit){}

void BaseManager::onUnitHide(BWAPI::Unit unit){}

void BaseManager::onUnitCreate(BWAPI::Unit unit){

}

void BaseManager::onUnitDestroy(BWAPI::Unit unit){

	if (unit->getPlayer() == BWAPI::Broodwar->self() && unit->getType().isResourceDepot())
	{
		for each(Base *b in allBases)
		{
			if (b->getHatch() == unit)
			{
				removeBase(unit);
			}
		}
	}
}

Base* BaseManager::getBase(BWAPI::TilePosition  location){
	
	for (std::set<Base*>::const_iterator iBase = allBases.begin(); iBase != allBases.end(); iBase++){
		if ((*iBase)->getBaseLocation() == location){
			return *iBase;
		}
	}
	
	return NULL;
	
}

void BaseManager::addBase(BWAPI::TilePosition  location,bool isEco)
{
	Base *newBase = new Base(location);

	if (isEco)
		allEcoBases.insert(newBase);
	else
		allBases.insert(newBase);
	
	updateNextBaseLocation();
}
void BaseManager::removeBase(BWAPI::Unit unit)
{
	for (std::set<Base*>::const_iterator iBase = allBases.begin(); iBase != allBases.end(); iBase++){
		if ((*iBase)->getHatch() == unit){
			iBase = allBases.erase(iBase);
			iBase--;
		}
	}
}

// !!!!!!!!!!!!!!!!!!! Sould only return base position and call morpher
void BaseManager::expand(){

	BWAPI::TilePosition  location;
	double minDist = -1;
	//BWTA::BaseLocation* home = BWTA::getStartLocation(BWAPI::Broodwar->self());    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	BWAPI::TilePosition  home;

	for (BWAPI::TilePosition tp : Broodwar->getStartLocations()){
		{
			double dist = home.getDistance(tp);

			if (dist > 0 && getBase(tp) == NULL)
			{
				if (minDist == -1 || dist < minDist)
				{
					minDist = dist;
					location = tp;
				}
			}
		}

		addBase(location, false);
	}
}

void BaseManager::updateNextBaseLocation(){

	BWAPI::TilePosition  location;
	double minDist = -1;

	for (BWAPI::TilePosition tp : Broodwar->getStartLocations()){
		{
			double dist = playerStartLocation.getDistance(tp);

			if (dist > 0 && getBase(tp) == NULL)
			{
				if (minDist == -1 || dist < minDist)
				{
					minDist = dist;
					location = tp;
				}
			}
		}

	}

	nextBaseLocation = location;
}

BWAPI::TilePosition BaseManager::getNewBaseLocation(){

	return nextBaseLocation;

}
void BaseManager::onUnitMorph(BWAPI::Unit unit){

	if (unit->getPlayer() == BWAPI::Broodwar->self()){
		if (unit->getType().isWorker()){
			createWorker(unit);
		}

		if (unit->getType().isResourceDepot() && unit->getType() != BWAPI::UnitTypes::Zerg_Lair && unit->getType() != BWAPI::UnitTypes::Zerg_Hive){
			createBase(unit);
		}
	}

	
}

void BaseManager::createBase(BWAPI::Unit unit){
	/*
	for (BWAPI::TilePosition tp : Broodwar->getStartLocations())
	{
		for (auto &e : BWAPI::Broodwar->getUnitsOnTile(tp))
		{
			BWAPI::Unit unitE = e;
			*/
	
	addBase(unit->getTilePosition(), true);
	//	}
	//}

}

void BaseManager::onUnitRenegade(BWAPI::Unit unit){}

void BaseManager::onSaveGame(std::string gameName){}

void BaseManager::onUnitComplete(BWAPI::Unit unit){}

Worker* BaseManager::getFreeWorker(){

	if (allFreeWorker.size() > 0){
		//BWAPI::Unit* workerUnit =   (*i)->getWorker();
		Worker* worker = *allFreeWorker.begin();
		allWorkingWorker.insert(*allFreeWorker.begin());
		allFreeWorker.erase(allFreeWorker.begin());
		return worker;
	}
	return NULL;

}

Worker* BaseManager::getBuilderWorker(){
	if (allFreeWorker.size() > 0){
		//BWAPI::Unit* workerUnit =   (*i)->getWorker();
		Worker* worker = *allFreeWorker.begin();
		allWorkingWorker.insert(*allFreeWorker.begin());
		allFreeWorker.erase(allFreeWorker.begin());
		return worker;
	}
	else{

		std::set<Base*>::iterator base = allBases.begin();
		Worker* worker = NULL;
		if ((*base)->assignedWorker.size() > 0){
			worker = (*base)->assignedWorker[0];
			(*base)->assignedWorker.erase((*base)->assignedWorker.begin());
		}
		return worker;
	}

	return NULL;
}

void BaseManager::freeAWorker(Worker *worker){

	std::set<Worker*>::iterator i = allWorkingWorker.find(worker);
	BWAPI::Unit workerUnit = (*i)->getWorker();
	allFreeWorker.insert(*i);
	allWorkingWorker.erase(i);
}

void BaseManager::removeWorker(BWAPI::Unit unit){

	for (std::set<Worker*>::const_iterator i = allWorkers.begin(); i != allWorkers.end(); i++){
		if ((*i)->getWorker() == unit){
			i = allWorkers.erase(i);
			i--;
		}
	}
}

void BaseManager::createWorker(BWAPI::Unit unit){
	unit->getTilePosition();
	Worker *worker = new Worker();
	(*worker).setWorker(unit);

	//*worker->worker = unit;
	allWorkers.insert(worker);
	allFreeWorker.insert(worker);
}

