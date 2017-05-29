#pragma once
#include <BWAPI.h>
#include <InformationManager.h>
#include <MoodManager.h>
#include <ArmyManager.h>
#include <MoneyManager.h>

class ArmyManager : public BWAPI::AIModule
{
public:
	ArmyManager();
	~ArmyManager();

	enum ActionsType{ Move, AttackMove, Defense, Patrol};
	enum ArmyOrder{ DestroyThisNoob, StayMain, MoveNearMain, DestroyExpansion, PatrolNearBase, None};

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

	//BWAPI::Unitset mainArmy;
	BWAPI::Unitset defenseArmy;

	void getAllArmy();

	BWAPI::Unit enemyNearBase = NULL;
	BWAPI::Unit pathTarget;

	BWAPI::Unit currentUnitTarget = NULL;

	std::set<BWAPI::Unit>	mainArmy;
	//std::set<BWAPI::Unit>	defenseArmy;

	//BWAPI::TilePosition target;
	BWAPI::PositionOrUnit target;
	bool updatedTarget = true;
	ArmyOrder order = ArmyOrder::StayMain;
	ArmyOrder previousOrder = ArmyOrder::None;;

	bool isArmyUnit(BWAPI::Unit unit);
	void addUnit(BWAPI::Unit unit);
	void removeUnit(BWAPI::Unit unit);

	void attackMove(BWAPI::TilePosition position);
	void moveTo(BWAPI::TilePosition position);
	void attack(BWAPI::Unit unit);

	void updateOrders();
	int lastTimeOrder = 0;

	InformationManager * informationManager;
	MoodManager *moodManager;
	MoneyManager *moneyManager;
};

