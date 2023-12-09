#include "listFile.h"

using namespace std;

queue <Field*> fieldsQueue;

set <Tractor*> tractors;
set <Harvester*> harvesters;

set <Tractor*> tractorsWait;
set <Harvester*> harvestersWait;

queue<Tractor*> tractorsQueue;
queue<Harvester*> harvestersQueue;

vector <fieldData_t> fieldsData;
vector <tractorData_t> tractorsData;
vector <harvesterData_t> harvestersData;



Facility tractorEmptyFac;
Facility help;

const double KG_WHEAT_PER_M2 = 0.4;
const int TIMETOEMPTY = 8;
const int TIME_TO_GET_TO_HARVESTER = 10;
const int WORK_TIME = 600;
const int TIME_TO_EMPTY_TRACTOR = 5;

int timeHarvestersWait = 0;
int timeTractorsWait = 0;

bool endSeason = false;


void reset() {
    timeHarvestersWait = 0;
    timeTractorsWait = 0;
    endSeason = false;

    tractorsWait.clear();
    harvestersWait.clear();

    while (!tractorsQueue.empty()) {
        tractorsQueue.pop();
    }

    while (!harvestersQueue.empty()) {
        harvestersQueue.pop();
    }

}

