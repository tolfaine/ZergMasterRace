#include "BuildOrderManager.h"
#include <time.h>

using namespace std;

BuildOrderManager::BuildOrderManager()
{
//	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 4));
//	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 5));
//	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 6));
///	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 7));
	//this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 8));
	//this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Overlord, 9));

	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Spawning_Pool, 9));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Extractor, 12));

	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Creep_Colony, 13));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hatchery, 15));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hydralisk_Den, 16));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hatchery, 18));

	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Lair, 20));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Creep_Colony, -1));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Creep_Colony, -1));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Creep_Colony, -1));
	this->techOrder.push_back(make_pair(BWAPI::TechTypes::Lurker_Aspect, 25));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Creep_Colony, -1));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Creep_Colony, -1));



//	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Creep_Colony, 18));



	//this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 24));
	//this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Lair, -1));
//	this->techOrder.push_back(make_pair(BWAPI::TechTypes::Lurker_Aspect, -1));

	//this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hatchery, -1));

	/*
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hatchery, -1));

	
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Queens_Nest, 40));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hive, 55));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hatchery, -1));

	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Ultralisk_Cavern, 65));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hatchery, -1));
	*/

	
	/*

	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Extractor,12));

	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Zergling, 15));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Zergling, 16));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Zergling, 17));

	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Lair, 18));

	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Zergling, 19));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Zergling, 20));
	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Zergling, 21));

	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hydralisk_Den, 24));
	*/


//	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 8));
//	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 9));
//	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 10));
//	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 11));
//	this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Drone, 12));
	//this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hatchery, 13));
	//this->buildOrder.push_back(make_pair(BWAPI::UnitTypes::Zerg_Hatchery, 300));


}


BuildOrderManager::~BuildOrderManager()
{
}


void BuildOrderManager::onStart()
{

}

void BuildOrderManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}
void BuildOrderManager::updateCanBuild(BWAPI::TechType type){

	if (type == BWAPI::TechTypes::Lurker_Aspect){
		canBuild.insert(BWAPI::UnitTypes::Zerg_Lurker);
		defaultAttackUnitType = BWAPI::UnitTypes::Zerg_Lurker;
	}
}

void  BuildOrderManager::updateCanBuild(BWAPI::UnitType type){

	if (type == BWAPI::UnitTypes::Zerg_Spawning_Pool){
		canBuild.insert(BWAPI::UnitTypes::Zerg_Zergling);
		defaultAttackUnitType = BWAPI::UnitTypes::Zerg_Zergling;
		mainUnitType = BWAPI::UnitTypes::Zerg_Zergling;

	}
	if (type == BWAPI::UnitTypes::Zerg_Hydralisk_Den){
		canBuild.insert(BWAPI::UnitTypes::Zerg_Zergling);
		mainUnitType = BWAPI::UnitTypes::Zerg_Hydralisk;
	}
	if (type == BWAPI::UnitTypes::Zerg_Ultralisk_Cavern){
		canBuild.insert(BWAPI::UnitTypes::Zerg_Ultralisk);
		defaultAttackUnitType = BWAPI::UnitTypes::Zerg_Zergling;
		mainUnitType = BWAPI::UnitTypes::Zerg_Ultralisk;
	}
}
BWAPI::UnitType BuildOrderManager::getUnitTypeToBuild(){

	srand(time(NULL));

	/*
	if (canBuild.size() == 0)
		return NULL;
		*/

	int randomIndex = rand() % 10;

	int minerals = BWAPI::Broodwar->self()->minerals();
	int gas = BWAPI::Broodwar->self()->gas();

	if (gas >300)
		return BWAPI::UnitTypes::Zerg_Hydralisk;
	if (gas < 100 )
		return BWAPI::UnitTypes::Zerg_Zergling;

	if (randomIndex < 5)
		return defaultAttackUnitType;
	else 
		return mainUnitType;
}

void BuildOrderManager::onFrame()
{
	// Check si on a un truc a build a notre supply on le build
	int sizeCurrentSupply = buildOrder.size();
	int sizeTechSupply = techOrder.size();

	if (sizeTechSupply > 0){

		if ((*unitsManager).currentSupply == techOrder.at(0).second || techOrder.at(0).second == -1){
			(*morphManager).tech(techOrder.at(0).first);
			//updateCanBuild(techOrder.at(0).first);
			techOrder.erase(techOrder.begin());
		}

	}

	if (!(*morphManager).isBusy()){

		if (sizeCurrentSupply > 0){
			if ((*unitsManager).currentSupply == buildOrder.at(0).second || buildOrder.at(0).second == -1){
				BWAPI::TilePosition position; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				(*morphManager).morph(buildOrder.at(0).first);
				//updateCanBuild(buildOrder.at(0).first);
				buildOrder.erase(buildOrder.begin());
			}
			else{
				if (lastSupply != (*unitsManager).currentSupply){


					if ((*baseManager).missingDrone > 0){
						lastSupply = (*unitsManager).currentSupply;
						(*morphManager).morph(BWAPI::UnitTypes::Zerg_Drone);
					}
					else{
						lastSupply = (*unitsManager).currentSupply;
						BWAPI::UnitType t;
						if (sizeCurrentSupply < 15)
							t = defaultAttackUnitType;
						else
							t = mainUnitType;
						if (t == NULL){
							(*morphManager).morph(BWAPI::UnitTypes::Zerg_Drone);
						}
						else
							(*morphManager).morph(t);
					}
				}

			}
		}
		else{

			if ((*moodManager).currentMood == MoodManager::MoodType::OFFENSIVE){
				BWAPI::UnitType t = getUnitTypeToBuild();
				if (t == NULL){
					(*morphManager).morph(BWAPI::UnitTypes::Zerg_Drone);
				}
				else
					(*morphManager).morph(t);
			}
		}

	}


	// Check si build Busy



	// Si vraiment vraiment plus rien rien, on passe enmode autonome.
	// En fonction du mood 
		// Prio Economie ou prio Attack ou prio Deffense
	// Si prio Eco, check si il manque worker. Check si on peut prendre base
	// Si prio Attack, Build unitées. Default units a build
	// Si prio Defense, Build unité de défense et attaque

}

void BuildOrderManager::onSendText(std::string text){}

void BuildOrderManager::onReceiveText(BWAPI::Player player, std::string text){}

void BuildOrderManager::onPlayerLeft(BWAPI::Player player){}

void BuildOrderManager::onNukeDetect(BWAPI::Position target){}

void BuildOrderManager::onUnitDiscover(BWAPI::Unit unit){}

void BuildOrderManager::onUnitEvade(BWAPI::Unit unit){}

void BuildOrderManager::onUnitShow(BWAPI::Unit unit){}

void BuildOrderManager::onUnitHide(BWAPI::Unit unit){}

void BuildOrderManager::onUnitCreate(BWAPI::Unit unit){}

void BuildOrderManager::onUnitDestroy(BWAPI::Unit unit){
	lastSupply = -1;
}

void BuildOrderManager::onUnitMorph(BWAPI::Unit unit){}

void BuildOrderManager::onUnitRenegade(BWAPI::Unit unit){}

void BuildOrderManager::onSaveGame(std::string gameName){}

void BuildOrderManager::onUnitComplete(BWAPI::Unit unit){}
