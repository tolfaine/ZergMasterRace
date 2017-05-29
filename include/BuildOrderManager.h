#pragma once
#include <BWAPI.h>
#include "SupplyManager.h"
#include "MorphManager.h"
#include "UnitsManager.h"
#include "MoodManager.h"
#include "BaseManager.h"

class BuildOrderManager : public BWAPI::AIModule
{
public:
	BuildOrderManager();
	~BuildOrderManager();

	std::vector<std::pair<BWAPI::UnitType, int>> buildOrder;

	std::vector<std::pair<BWAPI::TechType, int>> techOrder;

	bool freeBuilding = false;
	BWAPI::UnitType lastTypeMorphed;

	BWAPI::UnitType defaultAttackUnitType = BWAPI::UnitTypes::Zerg_Zergling;
	BWAPI::UnitType mainUnitType = BWAPI::UnitTypes::Zerg_Hydralisk;


	int lastSupply = 0;
	bool endBuild = false;
	std::set<BWAPI::UnitType> canBuild;

	void updateCanBuild(BWAPI::UnitType type);
	void updateCanBuild(BWAPI::TechType type);
	BWAPI::UnitType getUnitTypeToBuild();

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

	void buildNextUnit();

	SupplyManager *supplyManager;
	UnitsManager *unitsManager;
	MorphManager *morphManager;
	MoodManager *moodManager;
	BaseManager *baseManager;


};

