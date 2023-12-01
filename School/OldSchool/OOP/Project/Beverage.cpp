#include "Beverage.h"

Beverage::Beverage(std::string name, double size)
{
    this->name = name;
    this->size = size;
}

double Beverage::getSize()
{
    return this->size;
}

std::string Beverage::getName()
{
    return this->name;
}