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
    cout << "Day started" << endl;
    if (fieldsQueue.empty())
    {
        cout << "no fields" << endl;
        return;
    }
    if (fieldsQueue.front()->isHarvested())
    {
        cout << "pole skoncene" << endl;
        fieldsQueue.pop();
    }
    for(const auto& tractor : tractors)
    {
        cout << "aktivate tractor" << endl;
        tractor->Activate();
        cout << "traktor activated" << endl;

    } 
    for(const auto& harvester : harvesters)
    {
        cout << "aktivate harvester" << endl;
        harvester->Activate();
        cout << "harvester activated" << endl;
    }

    cout << "wait for work time" << endl;
    Wait(WORK_TIME);
    cout << "work time over" << endl;

    for(const auto& tractor : tractors)
    {
        cout << "end shift tractor" << endl;
        tractor->endShift();
        cout << "tractor shift ended" << endl;
    }
    for(const auto& harvester : harvesters)
    {
        cout << "end shift harvester" << endl;
        harvester->endShift();
        cout << "harvester shift ended" << endl;
    }
}

