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
    double maxSpeed;
    bool shiftEnded;
    Field* currentField;
public:
    int maxCapacity;
    int currentCapacity;
    Tractor(int maxCapacity, double maxSpeed);
    void Behavior() override;
    bool isFull();
    void endShift();
    void goToField();
    void emptyTractor();
    void endEmptying();
};



#endif // TRACTOR_H
