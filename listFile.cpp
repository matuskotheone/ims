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

bool endSeason = false;
