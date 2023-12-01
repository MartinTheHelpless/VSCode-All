#include "Customer.h"

Customer::Customer(int customerIndex, std::string beverage, double size)
{
    this->customerIndex = customerIndex;
    this->chosenBev = new Beverage(beverage, size);
}

Customer::~Customer()
{
    delete this;
}

int Customer::getCustIndex()
{
    return this->customerIndex;
}
