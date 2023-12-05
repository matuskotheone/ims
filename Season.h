#ifndef SEASON_H
#define SEASON_H

#include <queue>
#include <list>
#include <fstream>
#include <string>
#include <iostream>

#include "simlib.h"
#include "Field.h"
#include "Tractor.h"
#include "Harvester.h"
#include "Day.h"

class Day;

using namespace std;

class Season : public Event
{
private:
    int numberOfDays;
    int numberOfRainyDays;
public:
    Season();
    void Behavior() override;
    void PrintStats();
};
#endif // !SEASON_H
