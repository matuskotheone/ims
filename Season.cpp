#include "Season.h"

#DEFINE RAIN_CHANCE 0.1
#DEFINE HOUR_TO_MIN(x) x*60

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
    Wait(HOUR_TO_MIN(24));
    activate();
}

