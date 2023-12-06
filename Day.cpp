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
    if (fieldsQueue.front()->isHarvested())
    {
        fieldsQueue.pop();
    }
    if (fieldsQueue.empty())
    {
        return;
    }
    for(const auto& tractor : tractors)
    {
        tractor->Activate();

    } 
    for(const auto& harvester : harvesters)
    {
        harvester->Activate();
    }
    Wait(WORK_TIME);
    EndShifts();
}


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


