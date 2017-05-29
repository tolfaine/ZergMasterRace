#include "InformationManager.h"

using namespace BWAPI;

InformationManager::InformationManager()
{
}


InformationManager::~InformationManager()
{
}
void InformationManager::onStart()
{
	possibleEnemyStartLocations = Broodwar->getStartLocations();
	playerStartLocation = Broodwar->self()->getStartLocation();

	std::deque<BWAPI::TilePosition>::iterator it = possibleEnemyStartLocations.begin();
	while (it != possibleEnemyStartLocations.end()){

		if (*it == Broodwar->self()->getStartLocation()){
			it = possibleEnemyStartLocations.erase(it);
		}
		else{
			it++;
		}
	}
}

void InformationManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void InformationManager::onFrame()
{

}

void InformationManager::onSendText(std::string text){}

void InformationManager::onReceiveText(BWAPI::Player player, std::string text){}

void InformationManager::onPlayerLeft(BWAPI::Player player){}

void InformationManager::onNukeDetect(BWAPI::Position target){}

void InformationManager::onUnitDiscover(BWAPI::Unit unit){

	if (unit->getPlayer() != BWAPI::Broodwar->self()){


	}


}

void InformationManager::onUnitEvade(BWAPI::Unit unit){}

void InformationManager::onUnitShow(BWAPI::Unit unit){}

void InformationManager::onUnitHide(BWAPI::Unit unit){}

void InformationManager::onUnitCreate(BWAPI::Unit unit){}

void InformationManager::onUnitDestroy(BWAPI::Unit unit){}

void InformationManager::onUnitMorph(BWAPI::Unit unit){}

void InformationManager::onUnitRenegade(BWAPI::Unit unit){}

void InformationManager::onSaveGame(std::string gameName){}

void InformationManager::onUnitComplete(BWAPI::Unit unit){}
