#include "Season.h"

#define RAIN_CHANCE 0.1
#define HOUR_TO_MIN(x) x*60

class Day;

Season::Season()
{
    this->numberOfDays = 0;
    this->numberOfRainyDays = 0;
}

void Season::Behavior()
{
    if (fieldsQueue.empty())
    {
        PrintStats();
        endSeason = true;
        Tractor::ReleaseTractors();
        return;
    }
    if (Random() > RAIN_CHANCE)
    {
        (new Day())->Activate();
    }
    else 
    {
        numberOfRainyDays++;
    }

    numberOfDays++;
    Activate(Time + (60*24));
}


void Season::PrintStats()
{
    cout << "Pocet dnu: " << numberOfDays-1 << endl;
    cout << "Pocet destivych dnu: " << numberOfRainyDays << endl;
    cout << "Pocet slunecnych dnu: " << (numberOfDays-1) - numberOfRainyDays << endl;
    cout << "cas harvestery cakali: " << timeHarvestersWait / 60 << endl;
    cout << "cas traktoru cakali: " << timeTractorsWait / 60 << endl;
}
