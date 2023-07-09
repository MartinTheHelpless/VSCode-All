#include "Bank.h"

Bank::Bank()
{
    this->clientsCount = 0;
    this->clientsCount = 0;
}

Bank::~Bank()
{
    delete this;
}

Client *Bank::getClient(int id)
{
    for (int i = 0; i < this->accounts.size(); i++)
        if (this->clients[i]->getID() == id)
            return this->clients[i];

    return nullptr;
}

Client *Bank::createClient(int id, std::string name)
{
    this->clientsCount++;
    Client *newClient = new Client(name, id);
    this->clients.push_back(newClient);
    return newClient;
}

Account *Bank::getAccount(int id)
{
    for (int i = 0; i < this->accounts.size(); i++)
        if (this->accounts[i]->getId() == id)
            return this->accounts[i];

    return nullptr;
}

Account *Bank::createAccount(int id, Client *c)
{
    this->accountsCount++;
    Account *newAccount = new Account(id, c);
    this->accounts.push_back(newAccount);
    return newAccount;
}

Account *Bank::createAccount(int id, Client *c, double ir)
{
    this->accountsCount++;
    Account *newAccount = new Account(id, c, ir);
    this->accounts.push_back(newAccount);
    return newAccount;
}

void Bank::addInterest(Account *acc)
{
    acc->addInterest();
}