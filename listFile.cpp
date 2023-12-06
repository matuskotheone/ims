#include "listFile.h"

using namespace std;

queue <Field*> fieldsQueue;

set <Tractor*> tractors;
set <Harvester*> harvesters;

set <Tractor*> tractorsWait;
set <Harvester*> harvestersWait;

queue<Tractor*> tractorsQueue;
queue<Harvester*> harvestersQueue;

int timeHarvestersWait = 0;
int timeTractorsWait = 0;

int KG_WHEAT_PER_M2 = 4;
int TIMETOEMPTY = 8;
int TIME_TO_GET_TO_HARVESTER = 10;
int WORK_TIME = 480;
int TIME_TO_EMPTY_TRACTOR = 5;

Facility tractorEmptyFac;
Facility help;


bool endSeason = false;
