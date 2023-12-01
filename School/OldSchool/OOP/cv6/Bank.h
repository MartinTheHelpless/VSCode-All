#include "Account.cpp"
#pragma once

class Bank
{
private:
    std::vector<Client *> clients;
    int clientsCount;

    std::vector<Account *> accounts;
    int accountsCount;

public:
    Bank();
    ~Bank();

    Client *getClient(int id);
    Client *createClient(int id, std::string name);

    Account *getAccount(int id);
    Account *createAccount(int n, Client *c);
    Account *createAccount(int n, Client *c, double ir);

    void addInterest(Account *acc);
};