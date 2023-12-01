#pragma once
#include "Card.h"

Card::Card(std::string name, std::string type, std::string classType, int health, int damage)
{
    this->name = name;
    this->type = type;
    this->damage = damage;
    this->health = health;
    this->classType = classType;
}

void Card::setCardDamage(int setDmg)
{
    this->damage = setDmg;
}

void Card::setCardHealth(int health)
{
    this->health = health;
}

void Card::getDamage(int damage)
{
    damage <= 0 ? this->health : this->health -= damage;
}

void Card::addHealth(int amount)
{
    this->health += amount;
}

void Card::heal(int amount)
{
    this->health += amount;
    this->health >= this->origHealth ? this->health = origHealth : this->health;
}

void Card::setClassType(std::string type)
{
    this->classType = type;
}

void Card::setCardDescript(std::string descript)
{
    this->description = descript;
}

void Card::setFacePath(std::string path)
{
    this->face = path;
}

int Card::getCardDamage()
{
    return this->damage;
}

int Card::getCardHealth()
{
    return this->health;
}

std::string Card::getType()
{
    return this->type;
}

std::string Card::getClassType()
{
    return this->classType;
}