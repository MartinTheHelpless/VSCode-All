#pragma once
#include <iostream>
#include <vector>

class Client
{
private:
    std::string name;
    int id;

public:
    Client(std::string, int id);

    int getID();
    std::string getName();
};
