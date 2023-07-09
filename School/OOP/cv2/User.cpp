#include <string>

#include "User.h"

User::User(std::string name, int age, int height)
{
    this->name = name;
    this->age = age;
    this->height = height;
}

int User::getHeight()
{
    return this->height;
}
int User::getAge()
{
    return this->age;
}
std::string User::getName()
{
    return this->name;
}

void User::setHeight(int height)
{
    this->height = height;
}
void User::setAge(int age)
{
    this->age = age;
}
void User::setName(std::string name)
{
    this->name = name;
}

std::string User::toString()
{
    return this->name + " is " + std::to_string(this->age) + " yeas old and is " + std::to_string(this->height) + " cm tall.";
}