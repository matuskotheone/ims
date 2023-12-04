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
#define TIME_TO_GET_TO_HARVESTER 4


using namespace std;

extern queue<Field*> *fieldsQueue;

extern list <Tractor*> tractors;
extern list <Harvester*> harvesters;

extern set <Tractor*> tractorsWait;
extern set <Harvester*> harvestersWait;

extern queue<Tractor*> *tractorsQueue;
extern queue<Harvester*> *harvestersQueue;



#endif // LISTFILE_H

