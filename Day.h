#ifndef DAY_H
#define DAY_H

#include <queue>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "simlib.h"

#include "Tractor.h"
#include "Harvester.h"
#include "Season.h"
#include "Field.h"
#include "listFile.h"

class Season;

using namespace std;

class Day : public Process 
{
    public:
        Day();
        ~Day();
        void Behavior() override;
};

#endif
