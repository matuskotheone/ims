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

#define KG_WHEAT_PER_M2 4 
#define TIMETOEMPTY 8
#define TIME_TO_GET_TO_HARVESTER 10
#define WORK_TIME 480
#define AR_TO_M2(x) (x*100)
#define TON_TO_KG(x) (x*1000)

class Tractor;
class Harvester;

using namespace std;

extern queue<Field*> fieldsQueue;

extern set <Tractor*> tractors;
extern set <Harvester*> harvesters;

extern set <Tractor*> tractorsWait;
extern set <Harvester*> harvestersWait;

extern queue<Tractor*> tractorsQueue;
extern queue<Harvester*> harvestersQueue;

extern int timeHarvestersWait;
extern int timeTractorsWait;

extern bool endSeason;



#endif // LISTFILE_H
