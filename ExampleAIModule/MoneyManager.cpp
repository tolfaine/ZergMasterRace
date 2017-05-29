#include "MoneyManager.h"

void MoneyManager::onStart()
{

}

void MoneyManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void MoneyManager::onFrame()
{
	currentMinerals = BWAPI::Broodwar->self()->minerals();
	currentGas = BWAPI::Broodwar->self()->gas();

	calculateEffectiveRessources();



}
bool  MoneyManager::canUpgrade(BWAPI::UpgradeType type){
	int finaleMineral = effectiveMinerals - type.mineralPrice();
	int finalGas = effectiveGas - type.gasPrice();
	if (finaleMineral >= 0 && finalGas >= 0)
		return true;
	return false;
}

bool MoneyManager::canSearch(BWAPI::TechType type){
	int finaleMineral = effectiveMinerals - type.mineralPrice();
	int finalGas = effectiveGas - type.gasPrice();
	if (finaleMineral >= 0 && finalGas >= 0)
		return true;
	return false;
}

bool  MoneyManager::canBuild(BWAPI::UnitType type){

	int finaleMineral = effectiveMinerals - type.mineralPrice();
	int finalGas = effectiveGas - type.gasPrice();
	if (finaleMineral >= 0 && finalGas >= 0)
		return true;
	return false;
}

void MoneyManager::reserveRessources(Worker* worker, BWAPI::UnitType type){
	allQueuedReservations.push_back(std::make_pair(worker, type));
	calculateEffectiveRessources();

}

void MoneyManager::calculateEffectiveRessources(){

	reservedMinerals = 0;
	reservedGas = 0;

	std::vector<std::pair<Worker*, BWAPI::UnitType>>::iterator reservation = allQueuedReservations.begin();

	while (reservation != allQueuedReservations.end()){

		BWAPI::Unit unit = (*reservation).first->getWorker();

		//if (unit->isGatheringMinerals() || unit->isGatheringGas() || unit->isCarryingGas() || unit->isCarryingMinerals()){ // C'est pas ça dutout j'ai fumé 
		if (unit->getType().isWorker() && !unit->isIdle()){
			reservedMinerals += (*reservation).second.mineralPrice();
			reservedGas += (*reservation).second.gasPrice();
			reservation++;
		}
		else if (unit->getType().isWorker() && unit->isIdle()){
			BWAPI::TilePosition position = BWAPI::Broodwar->getBuildLocation((*reservation).second, unit->getTilePosition());
			unit->build((*reservation).second, position);
		}
		else{
			reservation = allQueuedReservations.erase(reservation);
		}

	}

	effectiveMinerals = currentMinerals - reservedMinerals;
	effectiveGas = currentGas - reservedGas;
}

void MoneyManager::onSendText(std::string text){}

void MoneyManager::onReceiveText(BWAPI::Player player, std::string text){}

void MoneyManager::onPlayerLeft(BWAPI::Player player){}

void MoneyManager::onNukeDetect(BWAPI::Position target){}

void MoneyManager::onUnitDiscover(BWAPI::Unit unit){}

void MoneyManager::onUnitEvade(BWAPI::Unit unit){}

void MoneyManager::onUnitShow(BWAPI::Unit unit){}

void MoneyManager::onUnitHide(BWAPI::Unit unit){}

void MoneyManager::onUnitCreate(BWAPI::Unit unit){}

void MoneyManager::onUnitDestroy(BWAPI::Unit unit){}

void MoneyManager::onUnitMorph(BWAPI::Unit unit){}

void MoneyManager::onUnitRenegade(BWAPI::Unit unit){}

void MoneyManager::onSaveGame(std::string gameName){}

void MoneyManager::onUnitComplete(BWAPI::Unit unit){}
