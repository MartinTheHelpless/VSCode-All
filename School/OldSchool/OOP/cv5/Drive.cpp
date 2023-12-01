#include "Drive.h"

Drive::Drive(Driver *driver, Car *car)
{
    this->driver = driver;
    this->car = car;
    this->positions = new Position *[10];
    this->positionCount = 0;
}

double Drive::getTotalDistance()
{
}

void Drive::addPosition(long double x, long double y)
{
    this->positions[this->positionCount] = new Position(x, y);
    this->positionCount++;
}