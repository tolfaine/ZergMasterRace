#include "ExampleAIModule.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;

void ExampleAIModule::onStart()
{
	//tempoManager = new TempoManager();
	textInfoManager = new TextInfoManager();
	buildOrderManager = new BuildOrderManager();
	unitsManager = new UnitsManager();
	supplyManager = new SupplyManager();
	morphManager = new MorphManager();
	moodManager = new MoodManager();
	baseManager = new BaseManager();
	informationManager = new InformationManager();
	workerManager = new WorkerManager();
	moneyManager = new MoneyManager();
	armyManager = new ArmyManager();
	defenseManager = new DefenseManager();

	(*buildOrderManager).moodManager = moodManager;
	(*buildOrderManager).morphManager = morphManager;
	(*buildOrderManager).unitsManager = unitsManager;
	(*buildOrderManager).supplyManager = supplyManager;
	(*buildOrderManager).baseManager = baseManager;
	(*supplyManager).unitsManager = unitsManager;
	(*supplyManager).morphManager = morphManager;
	(*morphManager).baseManager = baseManager;
	(*morphManager).moneyManager = moneyManager;
	(*morphManager).unitsManager = unitsManager;
	(*armyManager).informationManager = informationManager;
	(*armyManager).moodManager = moodManager;
	(*armyManager).moneyManager = moneyManager;
	(*defenseManager).moneyManager = moneyManager;

	//allModules.push_back(tempoManager);
	allModules.push_back(textInfoManager);
	allModules.push_back(buildOrderManager);
	allModules.push_back(unitsManager);
	allModules.push_back(supplyManager);
	allModules.push_back(morphManager);
	allModules.push_back(moodManager);
	allModules.push_back(baseManager);
	allModules.push_back(informationManager);
	allModules.push_back(workerManager);
	allModules.push_back(moneyManager);
	allModules.push_back(armyManager);
	allModules.push_back(defenseManager);

	for (BWAPI::AIModule* m : allModules)
	{
		m->onStart();
	}
}

void ExampleAIModule::onEnd(bool isWinner)
{
	for (BWAPI::AIModule* m : allModules)
	{
		m->onEnd(isWinner);
	}
}

void ExampleAIModule::onFrame()
{
	for (BWAPI::AIModule* m : allModules)
	{
		m->onFrame();
	}
}

void ExampleAIModule::onSendText(std::string text){

	for (BWAPI::AIModule* m : allModules)
	{
		m->onSendText(text);
	}
}

void ExampleAIModule::onReceiveText(BWAPI::Player player, std::string text){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onReceiveText(player,text);
	}
}

void ExampleAIModule::onPlayerLeft(BWAPI::Player player){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onPlayerLeft(player);
	}
}

void ExampleAIModule::onNukeDetect(BWAPI::Position target){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onNukeDetect(target);
	}
}

void ExampleAIModule::onUnitDiscover(BWAPI::Unit unit){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onUnitDiscover(unit);
	}
}

void ExampleAIModule::onUnitEvade(BWAPI::Unit unit){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onUnitEvade(unit);
	}
}

void ExampleAIModule::onUnitShow(BWAPI::Unit unit){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onUnitShow(unit);
	}
}

void ExampleAIModule::onUnitHide(BWAPI::Unit unit){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onUnitHide(unit);
	}
}

void ExampleAIModule::onUnitCreate(BWAPI::Unit unit){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onUnitCreate(unit);
	}
}

void ExampleAIModule::onUnitDestroy(BWAPI::Unit unit){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onUnitDestroy(unit);
	}
}

void ExampleAIModule::onUnitMorph(BWAPI::Unit unit){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onUnitMorph(unit);
	}
}

void ExampleAIModule::onUnitRenegade(BWAPI::Unit unit){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onUnitRenegade(unit);
	}
}

void ExampleAIModule::onSaveGame(std::string gameName){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onSaveGame(gameName);
	}
}

void ExampleAIModule::onUnitComplete(BWAPI::Unit unit){
	for (BWAPI::AIModule* m : allModules)
	{
		m->onUnitComplete(unit);
	}
}
