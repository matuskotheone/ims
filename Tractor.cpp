#include "Tractor.h"

Tractor::Tractor(double maxSpeed, int maxCapacity)
{
    this->maxCapacity = maxCapacity;
    this->maxSpeed = maxSpeed;
    this->currentCapacity = 0;
}

bool Tractor::isFull()
{
    return this->currentCapacity >= this->maxCapacity;
}


void Tractor::Behavior()
{
novyDen:
    cout << "THIS IS TRACTOR CAPACITY" << this->maxCapacity << endl;
    isReleased = false;

    tractorsWait.clear();
    tractorsQueue = queue<Tractor*>();
    cout << "tractor" << endl;
    currentCapacity = 0;
    shiftEnded = false;
    currentField = fieldsQueue.front();
    cout << "toto je current field distance" << currentField->distance << endl;
    goToField();
    while (true)
    {
        if (isFull())
        {
            cout << "idem vyprazdnovat" << endl;
            emptyTractor();
            cout << "vyprazdnil som" << endl;
        }
        cout << "tractor waiting" << endl;
        tractorsWait.insert(this);
        cout << "tractor to queue"<< endl;
        tractorsQueue.push(this);

        cout << "tractor in queeu" << endl;
        if (!harvestersQueue.empty())
        {
            Harvester* harvester = harvestersQueue.front();
            harvestersQueue.pop();
            harvestersWait.erase(harvester);
            harvester->Activate();
        }
        cout << "tractor waiting" << endl;
        Passivate();
        cout << "tractor activated" << endl;
        cout << this->currentCapacity << "out of " << this->maxCapacity << endl;
        cout << "shift ended " << shiftEnded << endl;
        if (shiftEnded)
        {
            cout << "shift ended" << endl;
            break;
        }
        endEmptying();
    }
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<< endl;
    Passivate();
    goto novyDen;
}

void Tractor::fillTractor(int ammount)
{
    currentCapacity += ammount;
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

void Tractor::ReleaseTractors()
{
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<< endl;
    for (Tractor* tractor : tractorsWait)
    {
        if (tractor->isReleased)
        {
            continue;
        }
        cout << "releasing tractor" << endl;
        tractor->isReleased = true;
        tractor->endShift();
        tractor->Activate();
        cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    }
}




void Tractor::endEmptying()
{
    Wait(TIME_TO_GET_TO_HARVESTER);
}
