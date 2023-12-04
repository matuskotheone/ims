#ifndef TRACTOR_H
#define TRACTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
    
#include "simlib.h"
#include "Field.h"
#include "Harvester.h"
#include "listFile.h"

using namespace std;

class Tractor : public Process
{
private: 
    int maxCapacity;
    int currentCapacity;
    double maxSpeed;
    bool shiftEnded;
    Field* currentField;
public:
    Tractor(int maxCapacity, double maxSpeed);
    void Behavior() override;
    bool isFull();
    void endShift();
    void goToField();
    void emptyTractor();
};



#endif // TRACTOR_H
