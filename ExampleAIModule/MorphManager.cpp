#include "MorphManager.h"

void MorphManager::onStart()
{

}

void MorphManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void MorphManager::onFrame()
{
	BWAPI::UnitType type = NULL;

	BWAPI::TilePosition position;

	if (BWAPI::Broodwar->getFrameCount() - lastChecked > 20){
		lastChecked = BWAPI::Broodwar->getFrameCount();

		if (techQueue.size()>0){
			if (moneyManager->canSearch(techQueue.at(0))){
				BWAPI::UnitType type = techQueue.at(0).whatResearches();

				BWAPI::Unit unit = unitsManager->getUnitOfType(type);

				if (unit != NULL){
					bool successfullyBuilt = unit->research(techQueue.at(0));



					if (successfullyBuilt){
						techQueue.erase(techQueue.begin());
					}
				}
			}
		}

		if (morphBuildingQueue.size() > 0){

			// GET A WORKER TO MORPH  
			if (moneyManager->canBuild(morphBuildingQueue.at(0))){

				Worker* worker = (*baseManager).getBuilderWorker();

				if (worker != NULL){
					BWAPI::Unit workerUnit = (*worker).getWorker();
					// position  =

					type = morphBuildingQueue.at(0);

					BWAPI::TilePosition positionWorker = workerUnit->getTilePosition();
					//position = BWAPI::Broodwar->getBuildLocation(type, baseManager->getNewBaseLocation(), 60);
					if (type == BWAPI::UnitTypes::Zerg_Hatchery)
						position = BWAPI::Broodwar->getBuildLocation(type, workerUnit->getTilePosition());
					else
						position = BWAPI::Broodwar->getBuildLocation(type, workerUnit->getTilePosition());  // NUL a chier , a changer  !!!!!!!!!!

					//BWAPI::UnitType type2 = BWAPI::UnitTypes::Zerg_Spawning_Pool;

					//	bool b = workerUnit->canMorph(type);
					//bool b2 = workerUnit->canMorph(BWAPI::UnitTypes::Zerg_Spawning_Pool);



					bool successfullyBuilt = workerUnit->build(type, position);
					if (successfullyBuilt){
						moneyManager->reserveRessources(worker, morphBuildingQueue.at(0));
						morphBuildingQueue.erase(morphBuildingQueue.begin());
					}
					else{
						(*baseManager).freeAWorker(worker);
					}
				}
			}
		}

		if (morphUnitsQueue.size() > 0){
			// GET A WORKER TO MORPH
			if (moneyManager->canBuild(morphUnitsQueue.at(0))){

				// BWAPI::Unit workerUnit = (*worker).getWorker();
				type = morphUnitsQueue.at(0);
				BWAPI::Unit base = NULL;
				Base *b = (*baseManager).getBaseWhoCanMorph(type);
				if (b != NULL){
					base = b->getHatch();

					// position  =

					//		BWAPI::Unit &wu = *workerUnit;
					//	BWAPI::TilePosition position = (BWAPI::Unit)(*wu);// .getTilePosition();

					// position = BWAPI::Broodwar->getBuildLocation(type, workerUnit->getTilePosition()); // NUL a chier , a changer  !!!!!!!!!!


					bool successfullyBuilt;

					if (type != BWAPI::UnitTypes::Zerg_Lair && type != BWAPI::UnitTypes::Zerg_Hive){
						successfullyBuilt = base->train(type);
					}
					else{
						successfullyBuilt = base->morph(type);
					}

					if (successfullyBuilt)
						morphUnitsQueue.erase(morphUnitsQueue.begin());
				}


			}
		}

	}


}
bool MorphManager::isBusy(){

	if(morphUnitsQueue.size() > 20 || morphBuildingQueue.size() > 20){
		return true;
	}
	return false;
}

void MorphManager::tech(BWAPI::TechType type){
	this->techQueue.push_back(type);
}

void MorphManager::morph(BWAPI::UnitType type){

	if (type.isBuilding() && type != BWAPI::UnitTypes::Zerg_Lair && type != BWAPI::UnitTypes::Zerg_Hive)
		this->morphBuildingQueue.push_back(type);
	else
		this->morphUnitsQueue.push_back(type);

}

void MorphManager::morphUrgent(BWAPI::UnitType type){

	if (type.isBuilding() && type != BWAPI::UnitTypes::Zerg_Lair && type != BWAPI::UnitTypes::Zerg_Hive)
		this->morphBuildingQueue.insert(morphBuildingQueue.begin(),type);
	else
		this->morphUnitsQueue.insert(morphUnitsQueue.begin(), type);

}

void MorphManager::onSendText(std::string text){}

void MorphManager::onReceiveText(BWAPI::Player player, std::string text){}

void MorphManager::onPlayerLeft(BWAPI::Player player){}

void MorphManager::onNukeDetect(BWAPI::Position target){}

void MorphManager::onUnitDiscover(BWAPI::Unit unit){}

void MorphManager::onUnitEvade(BWAPI::Unit unit){}

void MorphManager::onUnitShow(BWAPI::Unit unit){}

void MorphManager::onUnitHide(BWAPI::Unit unit){}

void MorphManager::onUnitCreate(BWAPI::Unit unit){}

void MorphManager::onUnitDestroy(BWAPI::Unit unit){

	if (unit->getPlayer() == BWAPI::Broodwar->self()){

		if (unit->getType().isBuilding()){

			BWAPI::UnitType unitType = NULL;

			if ((unit->getType() == BWAPI::UnitTypes::Zerg_Spawning_Pool)){
				unitType = BWAPI::UnitTypes::None;
			}
			if ((unit->getType() == BWAPI::UnitTypes::Zerg_Hydralisk_Den)){
				unitType = BWAPI::UnitTypes::Zerg_Hydralisk;
			}
			if ((unit->getType() == BWAPI::UnitTypes::Zerg_Ultralisk_Cavern)){
				unitType = BWAPI::UnitTypes::Zerg_Ultralisk;
			}

			if (unitType != NULL){

				std::vector<BWAPI::UnitType>::iterator it = morphBuildingQueue.begin();

				while (it != morphBuildingQueue.end()){

					if (*it == unitType){
						it = morphBuildingQueue.erase(it);
					}
					else{
						it++;
					}
				}
			}

			morphUrgent(unit->getType());
		}
	}


}

void MorphManager::onUnitMorph(BWAPI::Unit unit){}

void MorphManager::onUnitRenegade(BWAPI::Unit unit){}

void MorphManager::onSaveGame(std::string gameName){}

void MorphManager::onUnitComplete(BWAPI::Unit unit){}
