#include "ArmyManager.h"

using namespace BWAPI;
using namespace Filter;
using namespace UnitTypes;

ArmyManager::ArmyManager()
{
}


ArmyManager::~ArmyManager()
{
}

bool ArmyManager::isArmyUnit(BWAPI::Unit unit){


	if (unit->getPlayer() == BWAPI::Broodwar->self() && unit->getType() == Zerg_Devourer || unit->getType() == Zerg_Guardian || unit->getType() == Zerg_Hydralisk || unit->getType() == Zerg_Infested_Terran
		|| unit->getType() == Zerg_Lurker || unit->getType() == Zerg_Mutalisk || unit->getType() == Zerg_Scourge || unit->getType() == Zerg_Ultralisk
		|| unit->getType() == Zerg_Zergling || unit->getType() == Zerg_Queen)
		return true;
	return false;
}

void ArmyManager::addUnit(BWAPI::Unit unit){
	if (unit->getPlayer() == BWAPI::Broodwar->self() && isArmyUnit(unit)){
		mainArmy.insert(unit); //->insert(unit);
	}
}

void ArmyManager::removeUnit(BWAPI::Unit unit){
	if (unit->getPlayer() == BWAPI::Broodwar->self() && isArmyUnit(unit)){
		mainArmy.erase(unit);
	}
}

void ArmyManager::onStart()
{

}

void ArmyManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void ArmyManager::updateOrders(){

	if (moodManager->currentMood == MoodManager::MoodType::OFFENSIVE){
		if ((mainArmy.size() < 30 && order != ArmyOrder::DestroyThisNoob) || mainArmy.size() < 10){
			order = ArmyOrder::StayMain;
		}
		else{
			order = ArmyOrder::DestroyThisNoob;
			Position p;
			if (informationManager->foundEnemyStartLocation)
				p =Position(informationManager->enemyStartLocation.x*32, informationManager->enemyStartLocation.y*32);
			else
				p = Position(informationManager->possibleEnemyStartLocations.begin()->x*32, informationManager->possibleEnemyStartLocations.begin()->y*32);

			target = PositionOrUnit(p);
			updatedTarget = true;
		}
	}

}

void ArmyManager::getAllArmy(){
	for (auto &u : BWAPI::Broodwar->self()->getUnits())
	{
		if (!u->exists())
		{
			continue;
		}

		if (isArmyUnit(u)){
			mainArmy.insert(u);
		}
	}
}

void ArmyManager::onFrame()
{

	if (Broodwar->getFrameCount() - lastTimeOrder > 100){
		lastTimeOrder = Broodwar->getFrameCount();
		updateOrders();
		getAllArmy();
	}

	enemyNearBase = BWAPI::Broodwar->getClosestUnit(Position(BWAPI::Broodwar->self()->getStartLocation().x * 32, BWAPI::Broodwar->self()->getStartLocation().y * 32), Filter::IsEnemy,300);

	for each (BWAPI::Unit unit in mainArmy)
	{
		if (unit->getType() == BWAPI::UnitTypes::Zerg_Hydralisk){
			if (unit->canMorph(BWAPI::UnitTypes::Zerg_Lurker) && moneyManager->canBuild(BWAPI::UnitTypes::Zerg_Lurker)){
				unit->morph(BWAPI::UnitTypes::Zerg_Lurker);
			}
		}

	}


	if (order == ArmyOrder::DestroyThisNoob){// && previousOrder != order && updatedTarget){
		//mainArmy.attack(target);

		for each (BWAPI::Unit unit in mainArmy)
		{
			if (currentUnitTarget != NULL && currentUnitTarget->exists()){
				if (unit->canBurrow()){
					unit->burrow();
				}
				unit->attack(currentUnitTarget);
			}
			else{
				Unit enemy = NULL;
				Unitset set = unit->getUnitsInRadius(100, Filter::IsEnemy);
				for each (BWAPI::Unit unit in set)
				{
					if (unit->getType() == BWAPI::UnitTypes::Terran_Medic){
						enemy = unit;
					}

				}

				if (enemy == NULL){
					enemy = unit->getClosestUnit(Filter::IsEnemy, 150);
				}
				else{
					currentUnitTarget = enemy;
				}


				if (enemy != NULL){
					if (unit->canBurrow()){
						unit->burrow();
					}
					unit->attack(enemy);
				}
				else{
					if (unit->canUnburrow()){
						unit->unburrow();
					}
					unit->attack(target);
				}
			}
			
		}
	}
	else if (order == ArmyOrder::StayMain){// && previousOrder != order){
		//mainArmy.move(Position(BWAPI::Broodwar->self()->getStartLocation().x * 32, BWAPI::Broodwar->self()->getStartLocation().y*32));
		
		for each (BWAPI::Unit unit in mainArmy)
		{
			unit->move(Position(BWAPI::Broodwar->self()->getStartLocation().x * 32, BWAPI::Broodwar->self()->getStartLocation().y * 32));

			if (enemyNearBase != NULL){
				if (unit->canBurrow()){
					unit->burrow();
				}
				unit->attack(enemyNearBase);
			}
		}
	}

	previousOrder = order;
	updatedTarget = false;
		

}

void ArmyManager::attackMove(BWAPI::TilePosition position){

}
void ArmyManager::moveTo(BWAPI::TilePosition position){

}
void ArmyManager::attack(BWAPI::Unit unit){

}



void ArmyManager::onSendText(std::string text){}

void ArmyManager::onReceiveText(BWAPI::Player player, std::string text){}

void ArmyManager::onPlayerLeft(BWAPI::Player player){}

void ArmyManager::onNukeDetect(BWAPI::Position target){}

void ArmyManager::onUnitDiscover(BWAPI::Unit unit){}

void ArmyManager::onUnitEvade(BWAPI::Unit unit){}

void ArmyManager::onUnitShow(BWAPI::Unit unit){}

void ArmyManager::onUnitHide(BWAPI::Unit unit){}

void ArmyManager::onUnitCreate(BWAPI::Unit unit){}

void ArmyManager::onUnitDestroy(BWAPI::Unit unit){
	removeUnit(unit);
}

void ArmyManager::onUnitMorph(BWAPI::Unit unit){
	addUnit(unit);
}

void ArmyManager::onUnitRenegade(BWAPI::Unit unit){}

void ArmyManager::onSaveGame(std::string gameName){

}
void ArmyManager::onUnitComplete(BWAPI::Unit unit){

}
