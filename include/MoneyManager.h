#pragma once
#include <BWAPI.h>
#include <Worker.h>

class MoneyManager : public BWAPI::AIModule
{
public:
	MoneyManager(){};
	~MoneyManager(){};

	int currentMinerals = 0;
	int currentGas = 0;

	int effectiveMinerals = 0;
	int effectiveGas = 0;

	int reservedMinerals = 0;
	int reservedGas = 0;

	std::vector<std::pair<Worker*, BWAPI::UnitType>>  allQueuedReservations;

	bool canUpgrade(BWAPI::UpgradeType type);
	bool canSearch(BWAPI::TechType type);
	bool canBuild(BWAPI::UnitType type);
	void reserveRessources(Worker* worker, BWAPI::UnitType type);
	void calculateEffectiveRessources();

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


};

