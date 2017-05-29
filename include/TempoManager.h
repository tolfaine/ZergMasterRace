#pragma once
#include <BWAPI.h>

class TempoManager : public BWAPI::AIModule
{
public:
	TempoManager(){}
	~TempoManager(){}

	std::pair<int, bool> pool = std::make_pair(9, false);
	std::pair<int, bool> extractor = std::make_pair(9, false);
	std::pair<int, bool> b2 = std::make_pair(12, false);
	std::pair<int, bool> lair = std::make_pair(15, false);
	std::pair<int, bool> hydra = std::make_pair(17, false);


	int nbWorkers;
	std::string currentState = "No Action";
	bool productionBlocked = false;

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

