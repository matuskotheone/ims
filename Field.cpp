#include <Field.h>

Field::Field(int area, int distance)
{
    this->area = area;
    this->notHarvested = area;
    this->distance = distance;
}

void Field::harvest(int amount) // in meters squared
{
    notHarvested -= amount;
}

bool Field::isHarvested()
{
    return notHarvested <= 0;
}

int Field::getDistance()
{
    return distance;
}
