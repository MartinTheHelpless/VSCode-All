#include "Driver.h"

Driver::Driver(std::string name, int id)
{
    this->name = name;
    this->licenseID = id;
}

std::string Driver::getName()
{
    return this->name;
}

int Driver::getID()
{
    return this->licenseID;
}
