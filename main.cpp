#include <iostream>
#include <list>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>


#include "simlib.h"
#include "Tractor.h"
#include "Harvester.h"
#include "Season.h"
#include "Day.h"
#include "Field.h"
#include "listFile.h"

using namespace std;


int main(void)
{
    ifstream file;

    file.open("farma.txt");

    if (!file.is_open())
    {
        cout << "Chyba pri otvarani suboru" << endl;
        return 1;
    }

    string line;

    fieldsQueue = new queue<Field*>();

    while (getline(file, line))
    {
        if (line[0] == '#')
            continue;
        if (line[0] == 'F')
        {
            int area;
            int distance;
            sscanf(line.c_str(), "F %d %d", &area, &distance);
            fieldsQueue->push(new Field(area, distance));
        }
        else if (line[0] == 'T')
        {
            int speed, maxCapacity;
            sscanf(line.c_str(), "T %d %d", &speed, &maxCapacity);
            Tractor *t = new Tractor(speed, maxCapacity);
            tractors.insert(t);
        }
        else if (line[0] == 'H')
        {
            int maxSpeed, harvestSpeed, maxCapacity;
            sscanf(line.c_str(), "H %d %d %d", &maxSpeed, &harvestSpeed, &maxCapacity);
            Harvester *h = new Harvester(maxSpeed, harvestSpeed, maxCapacity);
            harvesters.insert(h);
        }
        else 
        {
            cout << "Chyba v subore" << endl;
            return 1;
        }
    }

    Init(0, 10000);
    SetStep(0.1);
    (new Season())->Activate();
    Run();
}
