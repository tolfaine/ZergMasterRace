#pragma once
#include <BWAPI.h>
#include <Worker.h>
#include <BaseManager.h>
#include <MoneyManager.h>
#include <UnitsManager.h>

class MorphManager : public BWAPI::AIModule
{
public:
	MorphManager(){};
	~MorphManager(){};

	std::vector<std::pair<Worker,BWAPI::UnitType>> workerOnTheirWayToBuild;
	std::vector<BWAPI::UnitType> morphUnitsQueue;
	std::vector<BWAPI::TechType> techQueue;
	std::vector<BWAPI::UnitType> morphBuildingQueue;

	int lastChecked = -1;
	// Building en construction
	// Upgrade in process


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

	void morph(BWAPI::UnitType type);
	void tech(BWAPI::TechType type);
	void morphUrgent(BWAPI::UnitType type);
	bool isBusy();

	BaseManager *baseManager;
	MoneyManager *moneyManager;
	UnitsManager * unitsManager;

};

