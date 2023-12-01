#pragma once
#include <iostream>

class Card
{
private:
    std::string name;
    int origHealth;
    int health;
    int damage;
    std::string classType;
    std::string type;
    std::string face; // this is the location of the file in computer -- path
    std::string description;

public:
    Card(std::string name, std::string type, std::string classType, int health, int damage);

    void setCardDamage(int setDmg);
    void setCardHealth(int health);
    void getDamage(int damage);
    void addHealth(int amount);
    void heal(int amount);
    void setClassType(std::string type);
    void setCardDescript(std::string descript);
    void setFacePath(std::string path);

    int getCardDamage();
    int getCardHealth();
    std::string getType();
    std::string getClassType();
};