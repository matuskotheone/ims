#include "Day.h"

Day::Day()
{
    //ctor
}

Day::~Day()
{
    //dtor
}


Day::Behavior::Behavior()
{
    if (fieldsQueue->front()->is_harvested())
    {
        fieldsQueue->pop();
    }
    for(const auto& tractor : tractors)
    {
        tractor->activate();
    } 
    for(const auto& harvester : harvesters)
    {
        harvester->activate();
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

