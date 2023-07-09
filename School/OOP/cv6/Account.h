#pragma once
#include "Client.cpp"

class Account
{
private:
    int id;
    double balance;
    double interestRate;

    Client *owner;

public:
    Account(int id, Client *cl);
    Account(int id, Client *cl, double ir);

    int getId();
    double getBalance();
    double getInterestRate();
    Client *getOwner();

    bool canWithdraw();

    void withdraw(int amount);
    void deposit(int amount);
    void addInterest();
};