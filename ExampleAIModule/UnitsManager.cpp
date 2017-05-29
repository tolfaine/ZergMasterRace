#include "UnitsManager.h"


UnitsManager::UnitsManager()
{
}


UnitsManager::~UnitsManager()
{
}

void UnitsManager::onStart()
{
	currentSupply = BWAPI::Broodwar->self()->supplyUsed();
}

void UnitsManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}
BWAPI::Unit  UnitsManager::getUnitOfType(BWAPI::UnitType type){

	for (auto &u : BWAPI::Broodwar->self()->getUnits())
	{
		if (u->exists() && u->isCompleted())
		{

			if (u->getType() == type)
				return u;

		}


	}
	return NULL;

}

void UnitsManager::onFrame()
{
	allUnitCount.clear();
	completedUnitCount.clear();
	incompleteUnitCount.clear();

	for (auto &u : BWAPI::Broodwar->self()->getUnits())
	{
		if (!u->exists())
		{
			continue;
		}

		++allUnitCount[u->getType()];
		if (u->isCompleted())
		{
			++completedUnitCount[u->getType()];
		}
		else
		{
			++incompleteUnitCount[u->getType()];
		}
	}


	currentSupply = BWAPI::Broodwar->self()->supplyUsed()/2;
	maxSupply = BWAPI::Broodwar->self()->supplyTotal() / 2;

}
int UnitsManager::getAllUnitTypeCount(BWAPI::UnitType type){
	return allUnitCount[type];
}

int UnitsManager::getIncompleteUnitTypeCount(BWAPI::UnitType type){
	return incompleteUnitCount[type];
}

int UnitsManager::getCompleteUnitTypeCount(BWAPI::UnitType type){
	return completedUnitCount[type];
}

void UnitsManager::onSendText(std::string text){}

void UnitsManager::onReceiveText(BWAPI::Player player, std::string text){}

void UnitsManager::onPlayerLeft(BWAPI::Player player){}

void UnitsManager::onNukeDetect(BWAPI::Position target){}

void UnitsManager::onUnitDiscover(BWAPI::Unit unit){}

void UnitsManager::onUnitEvade(BWAPI::Unit unit){}

void UnitsManager::onUnitShow(BWAPI::Unit unit){}

void UnitsManager::onUnitHide(BWAPI::Unit unit){}

void UnitsManager::onUnitCreate(BWAPI::Unit unit){}

void UnitsManager::onUnitDestroy(BWAPI::Unit unit){}

void UnitsManager::onUnitMorph(BWAPI::Unit unit){}

void UnitsManager::onUnitRenegade(BWAPI::Unit unit){}

void UnitsManager::onSaveGame(std::string gameName){}

void UnitsManager::onUnitComplete(BWAPI::Unit unit){}

