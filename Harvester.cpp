#include "Harvester.h"


Harvester::Harvester(int streetSpeed, int harvestSpeed, int maxCapacity, int ID)
{
    this->streetSpeed = streetSpeed;
    this->harvestSpeed = harvestSpeed;
    this->maxCapacity = maxCapacity;
    this->currentCapacity = 0;
    this->currentField = nullptr;
    this->ID = ID;
}

void Harvester::Behavior()
{
newDay:
    harvestersWait.clear(); // clear the set of harvesters waiting for tractors
    harvestersQueue = queue<Harvester*>(); // clear the queue of harvesters waiting for tractors
    tractor = nullptr; // clear the tractor
    shiftEnded = false; // set the shiftEnded flag to false
    currentCapacity = 0; // set the current capacity to 0

    currentField = fieldsQueue.front(); // get the first field from the queue

    goToField(); // go to the field
    while (1)
    {
        if (!isFull() && !currentField->isHarvested()) // if the harvester is not full and the field is not harvested
                                                       // yet then harvest
        {
            harvest();
            continue;
        }
        if (currentField->isHarvested()) // if the field is harvested end 
        {
            Day::EndShifts();
            break;
        }
        if (isFull() && shiftEnded) // if the harvester is full and shift ended end day
        {
            break;
        }
again:
        if (isFull())
        {
            if (tractorsQueue.empty()) // if there are no tractors waiting for harvester wait for tractor
            {
                if(!(harvestersWait.find(this)!=harvestersWait.end()))
                {
                    harvestersWait.insert(this);
                    harvestersQueue.push(this);
                }
                double time = Time;
                Passivate();// waiting
                timeHarvestersWait += (Time - time);
                goto again; // again check if there are tractors waiting
            }
            else
            {
                // if there are tractors waiting for harvester then get the first one
                Seize(help);// so the deadolock does not happen
                if (tractorsQueue.empty())
                {
                    Release(help);
                    goto again;
                }
                tractor = tractorsQueue.front();
                tractorsQueue.pop();
                tractorsWait.erase(tractor);
                Release(help);
            }
            emptyHarvester(); // empty the harvester
        }
    }
    Tractor::ReleaseTractors(); // release tractors waiting for harvester
    Passivate();
    if (!endSeason) // if the season is not ended then go to the next day
        goto newDay;
}

void Harvester::goToField()
{
    // go from the farm to the field
    Wait(currentField->distance / streetSpeed);
}

bool Harvester::isFull()
{
    // check if the harvester is full
    return currentCapacity >= maxCapacity;
}

void Harvester::harvest() // harvest a field for minute 
{
    Wait(1);
    currentField->harvest(harvestSpeed);
    currentCapacity += KG_WHEAT_PER_M2 * harvestSpeed;
}

void Harvester::endShift()
{
    shiftEnded = true; // set the shiftEnded flag to true
}

void Harvester::endHarvestSeason() // static function to relsear harvesters waiting for tractors
{
    for (const auto& harvester : harvesters)
    {
        harvester->endShift();
        harvester->Activate();
    }
}

void Harvester::emptyHarvester()
{
    // empty the harvester
    double time = Time;
    Wait(TIME_TO_GET_TO_HARVESTER);

    if (tractor == nullptr)
    {
        return;
    }

    for (int i = 0; i < TIMETOEMPTY; i++)
    {
        Wait(1);
        currentCapacity -= maxCapacity / TIMETOEMPTY;
        tractor->fillTractor(maxCapacity / TIMETOEMPTY);
        if (currentCapacity <= 0)
        {
            // stop emptying if the harvester is empty
            currentCapacity <= 0;
            break;
        }
        if (tractor->isFull())
        {
            // stop emptying if the tractor is full
            break;
        }
    }

    // count the time the tractor waited for the harvester
    timeTractorsWait -= Time - time - TIME_TO_GET_TO_HARVESTER;
    tractor->endEmptying();// signal the tractor that it is done emptying
    tractor = nullptr;
}
