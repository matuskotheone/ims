#include "Season.h"

#define RAIN_CHANCE 0.1
#define HOUR_TO_MIN(x) x*60

class Day;

Season::Season()
{
    this->numberOfDays = 0;
}

void Season::Behavior()
{
    cout << "kajlshdflkjashdflkjashdflkjashdflkjah" << endl;
    if (fieldsQueue.empty())
    {
        cout << "Konec sezony" << endl;
        endSeason = true;
        Tractor::ReleaseTractors();
        return;
    }
    if (Random() > RAIN_CHANCE)
    {
        (new Day())->Activate();
    }
    else 
    {
        cout << "prsi prsi prsi prsi prsi" << endl;
        numberOfRainyDays++;
    }

    numberOfDays++;
    Activate(Time + (60*24));
}

