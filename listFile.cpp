#include "listFile.h"

using namespace std;

queue <Field*> fieldsQueue;

set <Tractor*> tractors;
set <Harvester*> harvesters;

set <Tractor*> tractorsWait;
set <Harvester*> harvestersWait;

queue<Tractor*> tractorsQueue;
queue<Harvester*> harvestersQueue;
