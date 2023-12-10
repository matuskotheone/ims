#include "Day.h"




Day::Day()
{
    //ctor
}

Day::~Day()
{
    //dtor
}


void Day::Behavior()
{
    tractors.clear();
    harvesters.clear();
    // if last day the field was harvested, pop it from the queue
    if (fieldsQueue.front()->isHarvested())
    {
        fieldsQueue.pop();
    }
    // if there are no more fields to harvest, end the simulation
    if (fieldsQueue.empty())
    {
        return;
    }
    // get the next field to harvest
    for(const auto& tractor : tractorsData)
    {
        Tractor* newTractor = new Tractor(tractor.maxSpeed, tractor.maxCapacity, tractor.ID);
        tractors.insert(newTractor);
        newTractor->Activate();
    } 
    // activate all the tractors
    for(const auto& harvester : harvestersData)
    {
        Harvester* newHarvester = new Harvester(harvester.maxSpeed, harvester.harvestSpeed, harvester.maxCapacity, harvester.ID);
        harvesters.insert(newHarvester);
        newHarvester->Activate();
        //(new Harvester(harvester.maxSpeed, harvester.harvestSpeed, harvester.maxCapacity, harvester.ID))->Activate();
    }
    Wait(WORK_TIME);
    EndShifts();
    Wait(200);
    Tractor::ReleaseTractors();
}


// end the shifts of all the tractors and harvesters
void Day::EndShifts (){
    for(const auto& tractor : tractors)
    {
//	    cout << tractor->ID << endl;
//
	    if (tractor != nullptr && tractor->ID < 100)
		tractor->endShift();
    }
    for(const auto& harvester : harvesters)
    {
	    //cout << harvester->ID << endl;
	    if (harvester != nullptr && harvester->ID < 100)
		harvester->endShift();
    }
}


