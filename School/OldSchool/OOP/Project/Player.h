#pragma once
#include "Collection.cpp"

class Player
{
private:
    std::string name;
    int playClass;
    int maxHealth;
    int health;
    int damage;
    Collection *Collected;
    Collection **Decks;

public:
    Player(std::string name);
    ~Player();

    void changeName(std::string name);
    void takeDamage(int amount);
    void heal(int amount);
    void pickClass(int playClass);
    void setHealth(int health);
    void setMaxHealth(int mHealth);

    Collection *randomizeDeckOrder(Collection *deck);

    int getHealth();
    int getClass();
    std::string getName();
};