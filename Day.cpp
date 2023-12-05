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
    cout << "Day " << (Time/60/24) << endl;
    if (fieldsQueue.front()->isHarvested())
    {
        cout << "pupujem" << endl;
        fieldsQueue.pop();
    }
    if (fieldsQueue.empty())
    {
        cout << "nothing to do" << endl;
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
    cout << "padla ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
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


