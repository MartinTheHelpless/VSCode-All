#include "Car.h"

Car::Car(std::string spz, std::string vin, int id)
{
    this->SPZ = spz;
    this->VIN = vin;
    this->id = id;
}

std::string Car::getSPZ()
{
    return this->SPZ;
}

std::string Car::getVIN()
{
    return this->VIN;
}

int Car::getID()
{
    return this->id;
}
