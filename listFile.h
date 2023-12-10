#ifndef LISTFILE_H
#define LISTFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <list>
#include <queue>
#include <set>
 
#include "Tractor.h"
#include "Harvester.h"
#include "Field.h"

#include "simlib.h"

#define AR_TO_M2(x) (x*100)
#define TON_TO_KG(x) (x*1000)

class Tractor;
class Harvester;

using namespace std;

extern const double KG_WHEAT_PER_M2;
extern const int TIMETOEMPTY;
extern const int TIME_TO_GET_TO_HARVESTER;
extern const int WORK_TIME;
extern const int TIME_TO_EMPTY_TRACTOR;


struct FieldData {
    int area;
    int distance;
};
typedef struct FieldData fieldData_t;

struct TractorData {
    int maxSpeed;
    int maxCapacity;
    int ID;
};
typedef struct TractorData tractorData_t;

struct HarvesterData {
    int maxSpeed;
    int harvestSpeed;
    int maxCapacity;
    int ID;
};
typedef struct HarvesterData harvesterData_t;

extern vector <fieldData_t> fieldsData;
extern vector <tractorData_t> tractorsData;
extern vector <harvesterData_t> harvestersData;


extern queue<Field*> fieldsQueue;

extern set <Tractor*> tractors;
extern set <Harvester*> harvesters;

extern set <Tractor*> tractorsWait;
extern set <Harvester*> harvestersWait;

extern ofstream output;


extern queue<Tractor*> tractorsQueue;
extern queue<Harvester*> harvestersQueue;

extern int timeHarvestersWait;
extern int timeTractorsWait;

extern Facility help;

extern Facility tractorEmptyFac;

extern bool endSeason;
void reset();



#endif // LISTFILE_H
