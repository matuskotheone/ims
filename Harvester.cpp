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
                cout << "harvester " << ID << " is waiting for tractor" << endl;
                double time = Time;
                Passivate();
                Wait(1);
                timeHarvestersWait += (Time - time);
                goto again;
            }
            else
            {
                cout << "harvester " << ID << " is waiting for tractor" << endl;
                cout << "size of queue is " << tractorsQueue.size() << endl;
                cout << "size of wait is " << tractorsWait.size() << endl;
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
    double time = Time;
    Wait(TIME_TO_GET_TO_HARVESTER);

    cout << "tu som este " << endl;
    cout << tractor<< endl;
    if (tractor == nullptr)
    {
        cout << "tractor is nullptr" << endl;
        return;
    }

    cout << "tu som " << endl;
    cout << tractor->ID << endl; 

    cout << "into tractor " << tractor->ID << endl;

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
