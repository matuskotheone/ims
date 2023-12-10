#include "Season.h"

#define RAIN_CHANCE 0.3
#define HOUR_TO_MIN(x) x*60

class Day;

Season::Season()
{
    this->numberOfDays = 0;
    this->numberOfRainyDays = 0;
}

void Season::Behavior()
{
    if (fieldsQueue.empty()) // if there are no more fields to harvest end the simulation and print the results
    {
        PrintStats();
        pocet_dni(numberOfDays-1);
        pocet_dazd(numberOfRainyDays);
        pocet_pracovnych_dni((numberOfDays-1) - numberOfRainyDays);

        if (numberOfDays-1 == 0)
        {
            hodiny_harvester(0);
            hodiny_traktor(0);
        }
        else
        {
            hodiny_harvester(((timeHarvestersWait / 60)/(numberOfDays-1))/(float)harvestersData.size());
            hodiny_traktor(((timeTractorsWait / 60) / (numberOfDays-1))/(float)tractorsData.size());
        }

        endSeason = true;
        //Tractor::ReleaseTractors();
        return;
    }
    if (Random() > RAIN_CHANCE) // if it is not raining activate a new day
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


// print the resilts of the simulation
void Season::PrintStats()
{
    output << "Pocet dnu: " << numberOfDays-1 << endl;
    output << "Pocet destivych dnu: " << numberOfRainyDays << endl;
    output << "Pocet slunecnych dnu: " << (numberOfDays-1) - numberOfRainyDays << endl;
    output << "Priemerna doba cakania harvesteru v 1 den na poli: " << (timeHarvestersWait / 60)/(float)harvestersData.size() << " minut" << endl;
}
