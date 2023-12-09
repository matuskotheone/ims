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
#include "Stats.h"

using namespace std;

int main(void)
{
    ifstream file;

    RandomSeed(time(nullptr));


    file.open("farma.txt");

    if (!file.is_open())
    {
        cout << "Chyba pri otvarani suboru" << endl;
        return 1;
    }

    fieldsQueue = queue <Field*>();
    tractorsQueue = queue <Tractor*>();
    harvestersQueue = queue <Harvester*>();

    set <Field*> fields;

    int trak = 0;
    int harv = 0;


    string line;

    while (getline(file, line))
    {
        if (line[0] == '#')
            continue;
        if (line[0] == 'F')
        {
            int area;
            int distance;
            sscanf(line.c_str(), "F %d %d", &area, &distance);
            fields.insert(new Field(AR_TO_M2(area), distance));
            /*
            fieldData_t data;
            data.area = area;
            data.distance = distance;
            fieldsData.push_back(data);
            */
            //fieldsQueue.push(new Field(AR_TO_M2(area), distance));
        }
        else if (line[0] == 'T')
        {
            int speed, maxCapacity;
            sscanf(line.c_str(), "T %d %d", &speed, &maxCapacity);
            tractorData_t data;
            data.maxSpeed = speed;
            data.maxCapacity = TON_TO_KG(maxCapacity);
            data.ID = trak++;
            tractorsData.push_back(data);
            //tractorsData.push_back(listFile(speed, maxCapacity));
            //Tractor *t = new Tractor(speed, TON_TO_KG(maxCapacity), trak++);
            //tractors.insert(t);
        }
        else if (line[0] == 'H')
        {
            int maxSpeed, harvestSpeed, maxCapacity;
            sscanf(line.c_str(), "H %d %d %d", &maxSpeed, &harvestSpeed, &maxCapacity);
            harvesterData_t data;
            data.maxSpeed = maxSpeed;
            data.harvestSpeed = harvestSpeed;
            data.maxCapacity = TON_TO_KG(maxCapacity);
            data.ID = harv++;
            harvestersData.push_back(data);
        }
        //if the line is just white characters, skip it
        else if (line.find_first_not_of(' ') == string::npos)
            continue;
        else 
        {
            cout << "Chyba v subore" << endl;
            cout << line << endl;
            return 1;
        }
    }

    for (int i = 0;i < 100; i++)
    {

        reset();
        for (const auto& f : fields)
        {
            f->notHarvested = f->area;
            fieldsQueue.push(f);
        }
        Init(0, 100000);
        SetStep(0.001);
        (new Season())->Activate();
        Run();
    }
    pocet_dni.Output();
    pocet_dazd.Output();
    pocet_pracovnych_dni.Output();
    hodiny_harvester.Output();
    //hodiny_traktor.Output();
}
