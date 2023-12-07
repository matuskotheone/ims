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
    // if the tractor is filled to at least 90% of its capacity
    return this->currentCapacity >= (this->maxCapacity) * 0.9;
}


void Tractor::Behavior()
{
novyDen:
    isReleased = false;

    tractorsWait.clear();// clear the set of waiting tractors
    tractorsQueue = queue<Tractor*>();// clear the queue of waiting tractors
    currentCapacity = 0; // reset the current capacity of the tractor
    shiftEnded = false;// reset the shift ended flag
    currentField = fieldsQueue.front();// get the first field from the queue
    goToField();// go to the field

    while (true)
    {
        if (isFull() && !shiftEnded) // if the tractor is full and the shift has not ended
        {
            emptyTractor();
            if (shiftEnded)
            {
                break;
            }
        }

        if (isFull() && shiftEnded) // if the tractor is full and the shift has ended
        {
            break;
        }

        tractorsWait.insert(this); // insert the tractor into the set of waiting tractors
        tractorsQueue.push(this); // insert the tractor into the queue of waiting tractors

        // if there are harvesters waiting and the tractor is not full
        // release harvester that searvhes for the tracors waiting again
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
        Passivate();// wait for the harvester to take the tractor from queue fill it and release it 
        endEmptying();
        timeTractorsWait += Time - time;

        if (shiftEnded)
        {
            break;
        }
    }
    Passivate();// wait for the next day
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
    //Seize(tractorEmptyFac);
    Wait(60*(double(currentField->distance) / double(maxSpeed)));
    currentCapacity = 0;
    //Release(tractorEmptyFac);
    Wait(60*(double(currentField->distance) / double(maxSpeed)));
}


void Tractor::goToField()
{
    Wait(currentField->distance / maxSpeed);
}

void Tractor::endShift()
{
    shiftEnded = true;
}

void Tractor::ReleaseTractors() // relsease all tractors that are waiting
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
