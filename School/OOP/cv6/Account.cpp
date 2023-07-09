#include "Account.h"

Account::Account(int id, Client *cl)
{
    this->id = id;
    this->owner = cl;
    this->balance = 0;
}

Account::Account(int id, Client *cl, double ir)
{
    this->id = id;
    this->owner = cl;
    this->interestRate = ir;
}

int Account::getId()
{
    return this->id;
}

double Account::getBalance()
{
    return this->balance;
}

double Account::getInterestRate()
{
    return this->interestRate;
}

Client *Account::getOwner()
{
    return this->owner;
}

bool Account::canWithdraw()
{
    if (this->balance > 0)
        return true;
    return false;
}

void Account::withdraw(int amount)
{
    this->balance -= amount;
}

void Account::deposit(int amount)
{
    this->balance += amount;
}

void Account::addInterest()
{
    this->balance *= this->interestRate;
}