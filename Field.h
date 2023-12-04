#ifndef field_h
#define field_h

#include <iostream>
#include <list>
#include <cmath>
#include <algorithm>
#include <string>

#include "simlib.h"

using namespace std;

class Field
{
public:
    int area;
    int distance;
    int notHarvested;
    Field(int area, int distance);
    void harvest(int amount);
    bool isHarvested();
    int getDistance();
};
    

#endif // !field_h
