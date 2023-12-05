#ifndef HARVESTER_H
#define HARVESTER_H

#include <iostream>
#include <list>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

#include "Field.h"
#include "simlib.h"

#include "Tractor.h"
#include "Harvester.h"
#include "Day.h"

using namespace std;

class Tractor;
class Day;


class Harvester : public Process
{
private: 
    bool shiftEnded;
    int streetSpeed;
    int harvestSpeed;
    int maxCapacity;
    int currentCapacity;
    Field* currentField;
    void goToField();
    void harvest();
    Tractor* tractor;
    void emptyHarvester();
public:
    bool isFull();
    int ID;
    // hervestee speed 8m2/min 
    Harvester(int streetSpeed, int harvestSpeed, int maxCapacity, int ID);
    void Behavior() override;
    static void endHarvestSeason();

    void endShift();

};


#endif // !HARVESTER_H
