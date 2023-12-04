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
#include "listFile.h"

#include "Harvester.h"
#include "Tractor.h"

class Harvester;

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
        Tractor(double maxSpeed, int maxCapacity);
        void Behavior() override;
        bool isReleased;
        bool isFull();
        void endShift();
        void fillTractor(int ammount);
        void goToField();
        void emptyTractor();
        void endEmptying();
        static void ReleaseTractors();
};

#endif // TRACTOR_H
