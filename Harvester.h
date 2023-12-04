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


#include "Tractor.h"
#include "Field.h"



#include "simlib.h"

using namespace std;

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
    // hervestee speed 8m2/min 
    Harvester(int streetSpeed, int harvestSpeed, int maxCapacity);
    void Behavior() override;
    void endShift();

};


#endif // !HARVESTER_H
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
       //
