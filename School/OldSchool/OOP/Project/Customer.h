#pragma once
#include "Human.cpp"
#include "Beverage.cpp"

class Customer
{
private:
    int customerIndex;
    Beverage *chosenBev;

public:
    Customer(int customerIndex, std::string beverage, double size);
    ~Customer();

    int getCustIndex();
};