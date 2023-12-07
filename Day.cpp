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
    for(const auto& tractor : tractors)
    {
        tractor->Activate();

    } 
    // activate all the tractors
    for(const auto& harvester : harvesters)
    {
        harvester->Activate();
    }
    Wait(WORK_TIME);
    EndShifts();
}


// end the shifts of all the tractors and harvesters
void Day::EndShifts (){
    for(const auto& tractor : tractors)
    {
        tractor->endShift();
    }
    for(const auto& harvester : harvesters)
    {
        harvester->endShift();
    }
}


