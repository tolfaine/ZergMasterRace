#include "SupplyManager.h"

using namespace BWAPI;
using namespace Filter;

void SupplyManager::onStart()
{
	lastChecked = Broodwar->getFrameCount();
}

void SupplyManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void SupplyManager::onFrame()
{
	BWAPI::Error lastErr = BWAPI::Broodwar->getLastError();

	if ((*unitsManager).maxSupply == lastSupplyBlock-2 && (*unitsManager).currentSupply < lastSupplyBlock){
		lastSupplyBlock = -1;
	}

	if (Broodwar->getFrameCount() - lastChecked > 600 && lastSupplyBlock == (*unitsManager).maxSupply && (*unitsManager).maxSupply < 200){
		lastSupplyBlock = -1;
	}

	bool supplyblocked = (*unitsManager).currentSupply == (*unitsManager).maxSupply-2;
	int nbIncomplteOverloard = (*unitsManager).getIncompleteUnitTypeCount(BWAPI::UnitTypes::Zerg_Overlord);

	if (supplyblocked  &&
		nbIncomplteOverloard == 0 &&
		Broodwar->getFrameCount() - lastChecked > 400 && lastSupplyBlock != (*unitsManager).maxSupply){

		lastChecked = Broodwar->getFrameCount();
		lastSupplyBlock = (*unitsManager).maxSupply;
		(*morphManager).morphUrgent(BWAPI::UnitTypes::Zerg_Overlord);

	}

}

void SupplyManager::onSendText(std::string text){}

void SupplyManager::onReceiveText(BWAPI::Player player, std::string text){}

void SupplyManager::onPlayerLeft(BWAPI::Player player){}

void SupplyManager::onNukeDetect(BWAPI::Position target){}

void SupplyManager::onUnitDiscover(BWAPI::Unit unit){}

void SupplyManager::onUnitEvade(BWAPI::Unit unit){}

void SupplyManager::onUnitShow(BWAPI::Unit unit){}

void SupplyManager::onUnitHide(BWAPI::Unit unit){}

void SupplyManager::onUnitCreate(BWAPI::Unit unit){}

void SupplyManager::onUnitDestroy(BWAPI::Unit unit){

	if (unit->getType() == BWAPI::UnitTypes::Zerg_Overlord){
		lastSupplyBlock = -1;
	}

}

void SupplyManager::onUnitMorph(BWAPI::Unit unit){}

void SupplyManager::onUnitRenegade(BWAPI::Unit unit){}

void SupplyManager::onSaveGame(std::string gameName){}

void SupplyManager::onUnitComplete(BWAPI::Unit unit){}
