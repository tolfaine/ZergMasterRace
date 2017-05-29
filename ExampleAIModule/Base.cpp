#include "Base.h"


Base::Base(BWAPI::TilePosition  location)
{
	baseLocation = location;
}


Base::~Base()
{
}

void Base::setHatch(BWAPI::Unit unit){
	hatch = unit;
}



void Base::setActiveHatch(bool active){

}

void Base::setActiveGas(bool active){

}

BWAPI::TilePosition Base::getBaseLocation(){
	return baseLocation;
}

BWAPI::Unit Base::getHatch(){
	return hatch;
}

std::set<BWAPI::Unit>*  Base::getRefineries(){

	return NULL;

}

std::set<BWAPI::Unit>*  Base::getGeysers(){
	return  NULL;

}
void Base::setGeysers(std::set<BWAPI::Unit> geysers){


}


std::set<BWAPI::Unit>*  Base::getMinerals(){
	return  NULL;
}

void Base::setActiveMinerals(bool active){

}
