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
    if (fieldsQueue->front()->isHarvested())
    {
        fieldsQueue->pop();
    }
    for(const auto& tractor : tractors)
    {
        tractor->activate();
    } 
    for(const auto& harvester : harvesters)
    {
        harvester->Activate();
    }

    Wait(WORK_TIME);

    for(const auto& tractor : tractors)
    {
        tractor->endShift();
    }
    for(const auto& harvester : harvesters)
    {
        harvester->endShift();
    }
}

