#include "MoodManager.h"


MoodManager::MoodManager()
{
}


MoodManager::~MoodManager()
{
}

void MoodManager::onStart()
{

}

void MoodManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void MoodManager::onFrame()
{

}

void MoodManager::onSendText(std::string text){}

void MoodManager::onReceiveText(BWAPI::Player player, std::string text){}

void MoodManager::onPlayerLeft(BWAPI::Player player){}

void MoodManager::onNukeDetect(BWAPI::Position target){}

void MoodManager::onUnitDiscover(BWAPI::Unit unit){}

void MoodManager::onUnitEvade(BWAPI::Unit unit){}

void MoodManager::onUnitShow(BWAPI::Unit unit){}

void MoodManager::onUnitHide(BWAPI::Unit unit){}

void MoodManager::onUnitCreate(BWAPI::Unit unit){}

void MoodManager::onUnitDestroy(BWAPI::Unit unit){}

void MoodManager::onUnitMorph(BWAPI::Unit unit){}

void MoodManager::onUnitRenegade(BWAPI::Unit unit){}

void MoodManager::onSaveGame(std::string gameName){}

void MoodManager::onUnitComplete(BWAPI::Unit unit){}
