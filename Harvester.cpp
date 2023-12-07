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
    harvestersWait.clear();
    harvestersQueue = queue<Harvester*>();
    tractor = nullptr;
    shiftEnded = false;
    currentCapacity = 0;

    currentField = fieldsQueue.front();

    goToField();
    while (1)
    {
        if (!isFull() && !currentField->isHarvested())
        {
            harvest();
            continue;
        }
        if (currentField->isHarvested())
        {
            Day::EndShifts();
            break;
        }
        if (isFull() && shiftEnded)
        {
            break;
        }
again:
        if (isFull())
        {
            if (tractorsQueue.empty()) 
            {
                if(!(harvestersWait.find(this)!=harvestersWait.end()))
                {
                    harvestersWait.insert(this);
                    harvestersQueue.push(this);
                }
                double time = Time;
                Passivate();
                timeHarvestersWait += (Time - time);
                goto again;
            }
            else
            {
                Seize(help);
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
            emptyHarvester();
        }
    }
    Tractor::ReleaseTractors();
    Passivate();
    if (!endSeason)
        goto newDay;
}

void Harvester::goToField()
{
    Wait(currentField->distance / streetSpeed);
}

bool Harvester::isFull()
{
    return currentCapacity >= maxCapacity;
}

void Harvester::harvest()
{
    Wait(1);
    currentField->harvest(harvestSpeed);
    currentCapacity += KG_WHEAT_PER_M2 * harvestSpeed;
}

void Harvester::endShift()
{
    shiftEnded = true;
}

void Harvester::endHarvestSeason()
{
    for (const auto& harvester : harvesters)
    {
        harvester->endShift();
        harvester->Activate();
    }
}

void Harvester::emptyHarvester()
{
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
            currentCapacity = 0;
            break;
        }
        if (tractor->isFull())
        {
            break;
        }
    }

    timeTractorsWait -= Time - time - TIME_TO_GET_TO_HARVESTER;
    tractor->endEmptying();
    tractor = nullptr;
}
