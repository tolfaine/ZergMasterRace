#pragma once
#include <BWAPI.h>
#include "TempoManager.h"
#include "TextInfoManager.h"
#include "BuildOrderManager.h"
#include "WorkerManager.h"
#include "UnitsManager.h"
#include "SupplyManager.h"
#include "MorphManager.h"
#include "MoodManager.h"
#include "BaseManager.h"
#include "InformationManager.h"
#include "MoneyManager.h"
#include "ArmyManager.h"
#include "DefenseManager.h"

// Remember not to use "Broodwar" in any global class constructor!

class ExampleAIModule : public BWAPI::AIModule
{
public:
  // Virtual functions for callbacks, leave these as they are.
	TempoManager *tempoManager;
	TextInfoManager *textInfoManager;
	BuildOrderManager *buildOrderManager;
	WorkerManager *workerManager;
	UnitsManager *unitsManager;
	SupplyManager *supplyManager;
	MorphManager *morphManager;
	MoodManager *moodManager;
	BaseManager *baseManager;
	InformationManager * informationManager;
	MoneyManager * moneyManager;
	ArmyManager *armyManager;
	DefenseManager * defenseManager;

	std::list< BWAPI::AIModule* > allModules;

	virtual void onStart() override;
	virtual void onEnd(bool isWinner) override;
	virtual void onFrame() override;
	virtual void onSendText(std::string text) override;
	virtual void onReceiveText(BWAPI::Player player, std::string text) override;
	virtual void onPlayerLeft(BWAPI::Player player) override;
	virtual void onNukeDetect(BWAPI::Position target) override;
	virtual void onUnitDiscover(BWAPI::Unit unit) override;
	virtual void onUnitEvade(BWAPI::Unit unit) override;
	virtual void onUnitShow(BWAPI::Unit unit) override;
	virtual void onUnitHide(BWAPI::Unit unit) override;
	virtual void onUnitCreate(BWAPI::Unit unit) override;
	virtual void onUnitDestroy(BWAPI::Unit unit) override;
	virtual void onUnitMorph(BWAPI::Unit unit) override;
	virtual void onUnitRenegade(BWAPI::Unit unit) override;
	virtual void onSaveGame(std::string gameName) override;
	virtual void onUnitComplete(BWAPI::Unit unit) override;
  // Everything below this line is safe to modify.





};
