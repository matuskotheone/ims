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
            break;
        }
        if (isFull() && shiftEnded)
        {
            cout << "Harvester ended shift" << endl;
            break;
        }
again:
        if (isFull())
        {
            if (tractorsQueue.empty() && !(harvestersWait.find(this)!=harvestersWait.end()))
            {
                harvestersWait.insert(this);
                harvestersQueue.push(this);
                Passivate();
                goto again;
            }
            else
            {
                tractor = tractorsQueue.front();
                tractorsWait.erase(tractor);
            }
            emptyHarvester();
        }
    }
    Tractor::ReleaseTractors();
    cout << "#####################################################harvester leaving field" << endl;
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
        cout << "asdhlkjfffffakjfalsdhfkjhasldkfjhasdlkjfhaslkdjfhaslkdjfhashdjkf" << endl;
        Wait(1);
        currentCapacity -= maxCapacity / TIMETOEMPTY;
        cout << "current capacity: " << currentCapacity << endl;
        cout << "max capacity: " << maxCapacity << endl;
        tractor->fillTractor(maxCapacity / TIMETOEMPTY);
        if (currentCapacity <= 0)
        {
            currentCapacity = 0;
            break;
        }
        if (tractor->isFull())
        {
            cout << "tractor is full" << endl;
            break;
        }
    }
    tractor->endEmptying();
    tractor = nullptr;
    cout << "kapacita po vyprazdneni: " << currentCapacity << endl;
    cout << "mac capacity: " << maxCapacity << endl;
}
