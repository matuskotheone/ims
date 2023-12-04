#include "Harvester.h"

Harvester::Harvester(int streetSpeed, int harvestSpeed, int maxCapacity)
{
    this->streetSpeed = streetSpeed;
    this->harvestSpeed = harvestSpeed;
    this->maxCapacity = maxCapacity;
    this->currentCapacity = 0;
    this->currentField = nullptr;
}

void Harvester::Behavior()
{
    tractor = nullptr;
    shiftEnded = false;
    currentCapacity = 0;

    currentField = fieldsQueue->front();

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
            break;
        }
        if (isFull() && endShift)
        {
            break;
        }
again:
        if (isFull())
        {
            if (tractorsQueue->empty() && !(harvestersWait.find(this)!=harvestersWait.end()))
            {
                harvestersWait.insert(this);
                harvestersQueue->push(this);
                Passivate();
                goto again;
            }
            else
            {
                tractor = tractorsQueue->front();
                tractorsWait.erase(tractor);
            }
            emptyHarvester();
        }
    }
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
    currentCapacity+= KG_WHEAT_PER_M2 * harvestSpeed;
}

void Harvester::endShift()
{
    shiftEnded = true;
}

void Harvester::emptyHarvester()
{
    Wait(TIME_TO_GET_TO_HARVESTER);
    for (int i = 0; i < TIMETOEMPTY; i++)
    {
        Wait(1);
        currentCapacity -= maxCapacity / TIMETOEMPTY;
        tractor->currentCapacity += maxCapacity / TIMETOEMPTY;
        if (currentCapacity <= 0)
        {
            break;
        }
        if (tractor->isFull())
        {
            break;
        }
    }
    tractor->endEmptying();
    tractor = nullptr;
}
