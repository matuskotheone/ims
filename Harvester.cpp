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
    cout << " pole este treba " << currentField->notHarvested << endl;
    cout << " z  " << currentField->area << endl;

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
            cout << "field is harvested(((((((((((((((((((((((((((((((((((((((((((" << endl;
            cout << "time is: " << (int(Time/60))%24 << endl;
            Day::EndShifts();
            break;
        }
        if (isFull() && shiftEnded)
        {
            cout << "Harvester ended shift***************************************" << endl;
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
                tractorsQueue.pop();
                tractorsWait.erase(tractor);
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
    currentCapacity+= KG_WHEAT_PER_M2 * harvestSpeed;
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
    Wait(TIME_TO_GET_TO_HARVESTER);
    for (int i = 0; i < TIMETOEMPTY; i++)
    {
        Wait(1);
        currentCapacity -= maxCapacity / TIMETOEMPTY;
        tractor->fillTractor(maxCapacity / TIMETOEMPTY);
        if (currentCapacity <= 0)
        {
            /*
            cout << "##################################################################################" << endl;
            cout << "harvester ID is: " << ID << endl;
            cout << "harvester capacity is: " << currentCapacity << endl;
            cout << "out of " << maxCapacity << endl;
            cout << "tractor ID is: " << tractor->ID << endl;
            cout << "tractor capacity is: " << tractor->currentCapacity << endl;
            cout << "out of " << tractor->maxCapacity << endl;
            cout << "harvester is empty" << endl;
            cout << "##################################################################################" << endl;
            */
            currentCapacity = 0;
            break;
        }
        if (tractor->isFull())
        {
            cout << "tractor is full" << endl;
            break;
        }
    }
    cout << "Harvester ended emptying" << endl;
    tractor->endEmptying();
    tractor = nullptr;
}
