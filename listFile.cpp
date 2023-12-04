#include "listFile.h"

queue<Field*> *fieldsQueue;

list <Tractor*> tractors;
list <Harvester*> harvesters;

set <Tractor*> tractorsWait;
set <Harvester*> harvestersWait;



queue<Tractor*> *tractorsQueue;
queue<Harvester*> *harvestersQueue;
