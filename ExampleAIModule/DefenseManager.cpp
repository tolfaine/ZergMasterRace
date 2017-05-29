#include "DefenseManager.h"


DefenseManager::DefenseManager()
{
}


DefenseManager::~DefenseManager()
{
}

void DefenseManager::onStart()
{
	lastTime = 0;
}

void DefenseManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void DefenseManager::onFrame()
{

	if (BWAPI::Broodwar->getFrameCount() - lastTime > 50){
		lastTime = BWAPI::Broodwar->getFrameCount();

		for (auto &u : BWAPI::Broodwar->self()->getUnits()){

			if (u->getType() == BWAPI::UnitTypes::Zerg_Creep_Colony){

				if (u->canMorph(BWAPI::UnitTypes::Zerg_Sunken_Colony) && moneyManager->canBuild(BWAPI::UnitTypes::Zerg_Sunken_Colony)){
					u->morph(BWAPI::UnitTypes::Zerg_Sunken_Colony);
				}
			}

			if (u->getType() == BWAPI::UnitTypes::Zerg_Sunken_Colony){
				BWAPI::Unit enemy = u->getClosestUnit(BWAPI::Filter::IsEnemy, 200);
				if (enemy != NULL){
					if (u->canBurrow()){
						u->burrow();
					}
					u->attack(enemy);
				}
				else{
					if (u->canUnburrow()){
						u->unburrow();
					}
					u->attack(u);
				}
			}


	}


	}


}


void DefenseManager::onSendText(std::string text){}

void DefenseManager::onReceiveText(BWAPI::Player player, std::string text){}

void DefenseManager::onPlayerLeft(BWAPI::Player player){}

void DefenseManager::onNukeDetect(BWAPI::Position target){}

void DefenseManager::onUnitDiscover(BWAPI::Unit unit){}

void DefenseManager::onUnitEvade(BWAPI::Unit unit){}

void DefenseManager::onUnitShow(BWAPI::Unit unit){}

void DefenseManager::onUnitHide(BWAPI::Unit unit){}

void DefenseManager::onUnitCreate(BWAPI::Unit unit){}

void DefenseManager::onUnitDestroy(BWAPI::Unit unit){}

void DefenseManager::onUnitMorph(BWAPI::Unit unit){

	if (unit->getPlayer() == BWAPI::Broodwar->self()){



	}

}

void DefenseManager::onUnitRenegade(BWAPI::Unit unit){}

void DefenseManager::onSaveGame(std::string gameName){}

