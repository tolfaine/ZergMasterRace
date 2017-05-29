#include "WorkerManager.h"


WorkerManager::WorkerManager()
{
}


WorkerManager::~WorkerManager()
{
}
void WorkerManager::onStart()
{

}

void WorkerManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void WorkerManager::onFrame()
{
	// Check si  les workers de chaque base sont vivants
	// Requilibre les workers 

	// Check worker manquant && ceux imcomplete

	// demande les workers manquand au morpher
}

void WorkerManager::onSendText(std::string text){}

void WorkerManager::onReceiveText(BWAPI::Player player, std::string text){}

void WorkerManager::onPlayerLeft(BWAPI::Player player){}

void WorkerManager::onNukeDetect(BWAPI::Position target){}

void WorkerManager::onUnitDiscover(BWAPI::Unit unit){}

void WorkerManager::onUnitEvade(BWAPI::Unit unit){}

void WorkerManager::onUnitShow(BWAPI::Unit unit){}

void WorkerManager::onUnitHide(BWAPI::Unit unit){}

void WorkerManager::onUnitCreate(BWAPI::Unit unit){}

void WorkerManager::onUnitDestroy(BWAPI::Unit unit){}

void WorkerManager::onUnitMorph(BWAPI::Unit unit){}

void WorkerManager::onUnitRenegade(BWAPI::Unit unit){}

void WorkerManager::onSaveGame(std::string gameName){}

void WorkerManager::onUnitComplete(BWAPI::Unit unit){}
