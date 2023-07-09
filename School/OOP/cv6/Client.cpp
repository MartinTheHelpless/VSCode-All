#include "Client.h"


Client::Client(std::string, int id)
{
    this->name = name;
    this->id = id;
}

int Client::getID()
{
    return this->id;
}

std::string Client::getName()
{
    return this->name;
}