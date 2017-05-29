#include "ScoutManager.h"

void ScoutManager::onStart()
{

}

void ScoutManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void ScoutManager::onFrame()
{

}

void ScoutManager::onSendText(std::string text){}

void ScoutManager::onReceiveText(BWAPI::Player player, std::string text){}

void ScoutManager::onPlayerLeft(BWAPI::Player player){}

void ScoutManager::onNukeDetect(BWAPI::Position target){}

void ScoutManager::onUnitDiscover(BWAPI::Unit unit){}

void ScoutManager::onUnitEvade(BWAPI::Unit unit){}

void ScoutManager::onUnitShow(BWAPI::Unit unit){}

void ScoutManager::onUnitHide(BWAPI::Unit unit){}

void ScoutManager::onUnitCreate(BWAPI::Unit unit){}

void ScoutManager::onUnitDestroy(BWAPI::Unit unit){}

void ScoutManager::onUnitMorph(BWAPI::Unit unit){}

void ScoutManager::onUnitRenegade(BWAPI::Unit unit){}

void ScoutManager::onSaveGame(std::string gameName){}

void ScoutManager::onUnitComplete(BWAPI::Unit unit){}