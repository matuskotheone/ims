#include "Tractor.h"

Tractor::Tractor(int maxCapacity, double maxSpeed)
{
    this->maxCapacity = maxCapacity;
    this->maxSpeed = maxSpeed;
    this->currentCapacity = 0;
}

bool Tractor::isFull()
{
    return this->currentCapacity == this->maxCapacity;
}


void Tractor::Behavior()
{
    currentCapacity = 0;
    shiftEnded = false;
    currentField = fieldsQueue->front();
    goToField();
    while (true)
    {
        if (isFull())
        {
            emptyTractor();
        }
        tractorsQueue->push(this);
        tractorsWait.insert(this);
        if (!harvestersQueue->empty())
        {
            Harvester* harvester = harvestersQueue->front();
            harvestersQueue->pop();
            harvestersWait.erase(harvester);
            harvester->Activate();
        }
        Passivate();
        if (shiftEnded)
        {
            break;
        }
        endEmptying();
    }
}

void Tractor::emptyTractor()
{
    Wait(currentField->distance / maxSpeed);
    currentCapacity = 0;
    Wait(currentField->distance / maxSpeed);
}


void Tractor::goToField()
{
    Wait(currentField->distance / maxSpeed);
}

void Tractor::endShift()
{
    shiftEnded = true;
}

void Tractor::endEmptying()
{
    Wait(TIME_TO_GET_TO_HARVESTER);
}


