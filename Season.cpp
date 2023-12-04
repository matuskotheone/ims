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
        cout << "zapinam den" << endl;
        (new Day())->Activate();
    }
    else 
    {
        numberOfRainyDays++;
    }

    numberOfDays++;
    cout << "pocet dazdivych dni: " << numberOfRainyDays << endl;
    Activate(HOUR_TO_MIN(24));
    cout << "koniec dna" << endl;
}

