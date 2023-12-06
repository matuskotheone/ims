#include "Tractor.h"

int caka = 0;

Tractor::Tractor(double maxSpeed, int maxCapacity, int ID) 
{
    this->maxCapacity = maxCapacity;
    this->maxSpeed = maxSpeed;
    this->currentCapacity = 0;
    this->ID = ID;
}

bool Tractor::isFull()
{
    return this->currentCapacity >= (this->maxCapacity) * 0.9;
}


void Tractor::Behavior()
{
novyDen:
    isReleased = false;

    tractorsWait.clear();
    tractorsQueue = queue<Tractor*>();
    currentCapacity = 0;
    shiftEnded = false;
    currentField = fieldsQueue.front();
    goToField();

    while (true)
    {
        if (isFull() && !shiftEnded)
        {
            emptyTractor();
            if (shiftEnded)
            {
                break;
            }
        }
        if (isFull() && shiftEnded)
        {
            break;
        }
        tractorsWait.insert(this);
        tractorsQueue.push(this);

        if (!harvestersQueue.empty())
        {
            Harvester* harvester = harvestersQueue.front();
            harvestersQueue.pop();
            harvestersWait.erase(harvester);
            harvester->Activate();
        }
        /*
        */

        
        double time = Time;
        Passivate();
        timeTractorsWait += Time - time;

        if (shiftEnded)
        {
            break;
        }
        endEmptying();
    }
    caka++;
    Passivate();
    caka--;
    if (!endSeason)
    {
        goto novyDen;
    }
}

void Tractor::fillTractor(int ammount)
{
    currentCapacity += ammount;
}

void Tractor::emptyTractor()
{
    Wait(60*(double(currentField->distance) / double(maxSpeed)));
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

void Tractor::ReleaseTractors()
{
    for (Tractor* tractor : tractorsWait)
    {
        if (tractor->isReleased)
        {
            continue;
        }
        tractor->isReleased = true;
        tractor->endShift();
        tractor->Activate();
    }
}




void Tractor::endEmptying()
{
    Wait(TIME_TO_GET_TO_HARVESTER);
}
