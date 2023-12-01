#include <string>

#include "Car.h"

Car::Car(std::string make, std::string type, std::string color, int makeYear, int horsePower)
{
    this->make = make;
    this->type = type;
    this->color = color;
    this->makeYear = makeYear;
    this->horsePower = horsePower;
}

std::string Car::getMake()
{
    return this->make;
}
std::string Car::getType()
{
    return this->type;
}
std::string Car::getColor()
{
    return this->color;
}
int Car::getMakeYear()
{
    return this->makeYear;
}
int Car::getHP()
{
    return this->horsePower;
}

void Car::setMake(std::string make)
{
    this->make = make;
}
void Car::setType(std::string type)
{
    this->type = type;
}
void Car::setColor(std::string color)
{
    this->color = color;
}
void Car::setMakeYear(int year)
{
    this->makeYear = year;
}
void Car::setHP(int hp)
{
    this->horsePower = hp;
}

std::string Car::toString()
{
    return this->make + " " + this->type + " would be in " + this->color + ", year " + std::to_string(this->makeYear) + " and " + std::to_string(this->horsePower) + " stock.";
}