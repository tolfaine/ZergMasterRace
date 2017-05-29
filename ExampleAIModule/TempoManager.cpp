#include "TempoManager.h"
using namespace BWAPI;
using namespace Filter;

void TempoManager::onStart()
{

	currentState = "Start";
}

void TempoManager::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void TempoManager::onFrame()
{
	// Return if the game is a replay or is paused
	if (Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self())
		return;

	// Prevent spamming by only running our onFrame once every number of latency frames.
	// Latency frames are the number of frames before commands are processed.
	if (Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0)
		return;


	Broodwar->drawTextScreen(200, 60, "Current State : %s", currentState.c_str());

	std::map<const BWAPI::UnitType, int> allUnitCount;
	std::map<const BWAPI::UnitType, int> incompleteUnitCount;
	std::map<const BWAPI::UnitType, int> completedUnitCount;

	nbWorkers = 0;

	for (auto &u : Broodwar->self()->getUnits())
	{

		if (!u->exists())
		{
			continue;
		}

		++allUnitCount[u->getType()];
		if (u->isCompleted())
		{
			++completedUnitCount[u->getType()];
		}
		else
		{
			++incompleteUnitCount[u->getType()];
		}

		if (u->getType().isWorker()){
			nbWorkers++;
		}
	}


	// Iterate through all the units that we own
	for (auto &u : Broodwar->self()->getUnits())
	{
		// Ignore the unit if it no longer exists
		// Make sure to include this block when handling any Unit pointer!
		if (!u->exists())
			continue;

		// Ignore the unit if it has one of the following status ailments
		if (u->isLockedDown() || u->isMaelstrommed() || u->isStasised())
			continue;

		// Ignore the unit if it is in one of the following states
		if (u->isLoaded() || !u->isPowered() || u->isStuck())
			continue;

		// Ignore the unit if it is incomplete or busy constructing
		if (!u->isCompleted() || u->isConstructing())
			continue;

		// Finally make the unit do some stuff!
		if ((u->getType() == UnitTypes::Zerg_Hydralisk) && u->isIdle())
		{
			Unit closestEnemy = NULL;
			for (auto &e : Broodwar->enemy()->getUnits())
			{
				if ((closestEnemy == NULL) || (e->getDistance(u) < closestEnemy->getDistance(u)))
				{
					closestEnemy = e;
				}
			}
			u->attack(closestEnemy, false);
		}

		// If the unit is a worker unit
		if (u->getType().isWorker())
		{

			if (!pool.second && nbWorkers >= pool.first){

				currentState = "Build Pool";

				if (!productionBlocked && Broodwar->self()->minerals() >= UnitTypes::Zerg_Spawning_Pool.mineralPrice())
				{
					//find a location for spawning pool and construct it
					TilePosition buildPosition = Broodwar->getBuildLocation(BWAPI::UnitTypes::Zerg_Spawning_Pool, u->getTilePosition());
					u->build(UnitTypes::Zerg_Spawning_Pool, buildPosition);

					productionBlocked = true;
				}
				if (allUnitCount[UnitTypes::Zerg_Spawning_Pool] > 0){
					productionBlocked = false;
					pool.second = true;
				}
			}
			else if (!extractor.second && nbWorkers >= extractor.first){

				currentState = "Build extractor";

				if (!productionBlocked && Broodwar->self()->minerals() >= UnitTypes::Zerg_Extractor.mineralPrice())
				{
					//find a location for spawning pool and construct it
					TilePosition buildPosition = Broodwar->getBuildLocation(BWAPI::UnitTypes::Zerg_Extractor, u->getTilePosition());
					u->build(UnitTypes::Zerg_Extractor, buildPosition);
					productionBlocked = true;
				}
				if (allUnitCount[UnitTypes::Zerg_Extractor] > 0){
					productionBlocked = false;
					extractor.second = true;
				}
			}
			else if (!b2.second && nbWorkers >= b2.first){

				currentState = "Build B2";

				if (!productionBlocked && Broodwar->self()->minerals() >= UnitTypes::Zerg_Hatchery.mineralPrice())
				{
					//find a location for spawning pool and construct it
					TilePosition buildPosition = Broodwar->getBuildLocation(BWAPI::UnitTypes::Zerg_Hatchery, u->getTilePosition());
					u->build(UnitTypes::Zerg_Hatchery, buildPosition);
					productionBlocked = true;

				}
				if (allUnitCount[UnitTypes::Zerg_Hatchery] > 1){
					productionBlocked = false;
					b2.second = true;
				}
			}
			else if (!lair.second  && nbWorkers >= lair.first){

				currentState = "Build lair";

			}
			else if (!hydra.second && nbWorkers >= hydra.first){

				currentState = "Build hydra";

				if (!productionBlocked && Broodwar->self()->minerals() >= UnitTypes::Zerg_Hydralisk_Den.mineralPrice())
				{
					//find a location for spawning pool and construct it
					TilePosition buildPosition = Broodwar->getBuildLocation(BWAPI::UnitTypes::Zerg_Hydralisk_Den, u->getTilePosition());
					u->build(UnitTypes::Zerg_Hydralisk_Den, buildPosition);
					productionBlocked = true;
				}
				if (allUnitCount[UnitTypes::Zerg_Hydralisk_Den] >= 1){
					productionBlocked = false;
					hydra.second = true;
				}
			}
			else{
				currentState = "end build";
			}



			// if our worker is idle
			if (u->isIdle())
			{
				// Order workers carrying a resource to return them to the center,
				// otherwise find a mineral patch to harvest.
				if (u->isCarryingGas() || u->isCarryingMinerals())
				{
					u->returnCargo();
				}
				else if (!u->getPowerUp())  // The worker cannot harvest anything if it
				{                             // is carrying a powerup such as a flag
					// Harvest from the nearest mineral patch or gas refinery
					if (!u->gather(u->getClosestUnit(IsMineralField || IsRefinery)))
					{
						// If the call fails, then print the last error message
						Broodwar << Broodwar->getLastError() << std::endl;
					}

				} // closure: has no powerup
			} // closure: if idle

		}

		else if (u->getType().isResourceDepot()) // A resource depot is a Command Center, Nexus, or Hatchery
		{



			// Order the depot to construct more workers! But only when it is idle.
			if ((nbWorkers != pool.first || (nbWorkers == pool.first && pool.second) && nbWorkers != extractor.first || (nbWorkers == extractor.first && extractor.second)
				&& nbWorkers != b2.first || (nbWorkers == b2.first && b2.second) && nbWorkers != lair.first || (nbWorkers == lair.first && lair.second)
				&& nbWorkers != hydra.first || (nbWorkers == hydra.first && hydra.second)))
			{


				if (hydra.second){
					u->train(UnitTypes::Zerg_Zergling);
				}

				if (!hydra.second && u->isIdle() && !u->train(u->getType().getRace().getWorker()))
					currentState = "Build Worker";
				//	if (pool && u->isIdle() && !u->train(UnitTypes::Zerg_Zergling))
				{
					// If that fails, draw the error at the location so that you can visibly see what went wrong!
					// However, drawing the error once will only appear for a single frame
					// so create an event that keeps it on the screen for some frames
					Position pos = u->getPosition();
					Error lastErr = Broodwar->getLastError();
					Broodwar->registerEvent([pos, lastErr](Game*){ Broodwar->drawTextMap(pos, "%c%s", Text::White, lastErr.c_str()); },   // action
						nullptr,    // condition
						Broodwar->getLatencyFrames());  // frames to run

					// Retrieve the supply provider type in the case that we have run out of supplies
					UnitType supplyProviderType = u->getType().getRace().getSupplyProvider();
					static int lastChecked = 0;

					//	Broodwar->drawTextScreen(200, 80, "SupplyProvider incomplete : %d", Broodwar->self()->incompleteUnitCount(supplyProviderType));
					// If we are supply blocked and haven't tried constructing more recently

					if (b2.second && !lair.second){
						u->morph(BWAPI::UnitTypes::Zerg_Lair);
						lair.second = true;
					}


					if (lastErr == Errors::Insufficient_Supply &&
						lastChecked + 400 < Broodwar->getFrameCount() &&
						Broodwar->self()->incompleteUnitCount(supplyProviderType) == 0)
					{

						lastChecked = Broodwar->getFrameCount();

						// Retrieve a unit that is capable of constructing the supply needed
						Unit supplyBuilder = u->getClosestUnit(GetType == supplyProviderType.whatBuilds().first &&
							(IsIdle || IsGatheringMinerals) &&
							IsOwned);


						// Broodwar->drawTextScreen(200, 50, "SupplyProvider type: %s", supplyProviderType.toString());

						// If a unit was found
						if (supplyBuilder)
						{
							if (supplyProviderType.isBuilding())
							{
								TilePosition targetBuildLocation = Broodwar->getBuildLocation(supplyProviderType, supplyBuilder->getTilePosition());
								if (targetBuildLocation)
								{
									// Register an event that draws the target build location
									Broodwar->registerEvent([targetBuildLocation, supplyProviderType](Game*)
									{
										Broodwar->drawBoxMap(Position(targetBuildLocation),
											Position(targetBuildLocation + supplyProviderType.tileSize()),
											Colors::Blue);
									},
										nullptr,  // condition
										supplyProviderType.buildTime() + 100);  // frames to run

									// Order the builder to construct the supply structure
									supplyBuilder->build(supplyProviderType, targetBuildLocation);
								}
							}
							else
							{
								// Train the supply provider (Overlord) if the provider is not a structure
								supplyBuilder->train(supplyProviderType);
							}
						} // closure: supplyBuilder is valid
					} // closure: insufficient supply
				} // closure: failed to train idle unit
			}
		}

	} // closure: unit iterator
}

void TempoManager::onSendText(std::string text){}

void TempoManager::onReceiveText(BWAPI::Player player, std::string text){}

void TempoManager::onPlayerLeft(BWAPI::Player player){}

void TempoManager::onNukeDetect(BWAPI::Position target){}

void TempoManager::onUnitDiscover(BWAPI::Unit unit){}

void TempoManager::onUnitEvade(BWAPI::Unit unit){}

void TempoManager::onUnitShow(BWAPI::Unit unit){}

void TempoManager::onUnitHide(BWAPI::Unit unit){}

void TempoManager::onUnitCreate(BWAPI::Unit unit){}

void TempoManager::onUnitDestroy(BWAPI::Unit unit){}

void TempoManager::onUnitMorph(BWAPI::Unit unit){}

void TempoManager::onUnitRenegade(BWAPI::Unit unit){}

void TempoManager::onSaveGame(std::string gameName){}

void TempoManager::onUnitComplete(BWAPI::Unit unit){}
