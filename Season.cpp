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
    if (Random() > RAIN_CHANCE)
    {
        (new Day())->Activate();
    }
    else 
    {
        numberOfRainyDays++;
    }

    numberOfDays++;
    Activate(HOUR_TO_MIN(24));
}

