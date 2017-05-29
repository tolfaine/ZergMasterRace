#pragma once
#include <BWAPI.h>

// Remember not to use "Broodwar" in any global class constructor!

class ExampleAIModule : public BWAPI::AIModule
{
public:
  // Virtual functions for callbacks, leave these as they are.

	std::list< BWAPI::AIModule* > m_modules;


	std::pair<int, bool> pool = std::make_pair(9, false);
	std::pair<int, bool> extractor = std::make_pair(9, false);
	std::pair<int, bool> b2 = std::make_pair(12, false);
	std::pair<int, bool> lair = std::make_pair(15, false);
	std::pair<int, bool> hydra = std::make_pair(17, false);


	int nbWorkers;
	std::string currentState = "No Action";
	bool productionBlocked = false;
	
  virtual void onStart();	
  virtual void onEnd(bool isWinner);
  virtual void onFrame();
  virtual void onSendText(std::string text);
  virtual void onReceiveText(BWAPI::Player player, std::string text);
  virtual void onPlayerLeft(BWAPI::Player player);
  virtual void onNukeDetect(BWAPI::Position target);
  virtual void onUnitDiscover(BWAPI::Unit unit);
  virtual void onUnitEvade(BWAPI::Unit unit);
  virtual void onUnitShow(BWAPI::Unit unit);
  virtual void onUnitHide(BWAPI::Unit unit);
  virtual void onUnitCreate(BWAPI::Unit unit);
  virtual void onUnitDestroy(BWAPI::Unit unit);
  virtual void onUnitMorph(BWAPI::Unit unit);
  virtual void onUnitRenegade(BWAPI::Unit unit);
  virtual void onSaveGame(std::string gameName);
  virtual void onUnitComplete(BWAPI::Unit unit);
  // Everything below this line is safe to modify.

};
