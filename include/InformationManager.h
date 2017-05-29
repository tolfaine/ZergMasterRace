#pragma once
#include <BWAPI.h>
#include <BWTA/BaseLocation.h>

class InformationManager : public BWAPI::AIModule
{
public:
	InformationManager();
	~InformationManager();

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

	std::deque<BWAPI::TilePosition>	possibleEnemyStartLocations;
	BWAPI::TilePosition		enemyStartLocation;
	bool foundEnemyStartLocation = false;

	BWAPI::TilePosition			playerStartLocation;
	std::set<BWAPI::TilePosition>	playerBasesLocations;

	std::set<BWAPI::TilePosition>	enemyBasesLocations;
	std::set<BWAPI::Unit>	enemyBuildings;


};

