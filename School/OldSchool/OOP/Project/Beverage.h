#pragma once
#include <iostream>

class Beverage
{
private:
    double size;
    std::string name;

public:
    Beverage(std::string name, double size);

    double getSize();

    std::string getName();
};