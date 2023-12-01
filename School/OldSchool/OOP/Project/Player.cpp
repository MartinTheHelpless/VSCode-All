#pragma once
#include "Player.h"
#include <time.h>

Player::Player(std::string name)
{
    this->name = name;
}

Player::~Player()
{
    delete this;
}

void Player::changeName(std::string name)
{
    this->name = name;
}

void Player::takeDamage(int amount)
{
    this->health -= amount;
}

void Player::heal(int amount)
{
    this->health += amount;
    this->health >= this->maxHealth ? this->health = this->maxHealth : this->health;
}

void Player::pickClass(int playClass)
{
    this->playClass = playClass;
}

void Player::setHealth(int health)
{
    this->health = health;
}

void Player::setMaxHealth(int mHealth)
{
    this->maxHealth = mHealth;
}

Collection *Player::randomizeDeckOrder(Collection *deck)
{
    Collection *tempDeck = new Collection(30);

    srand(time(nullptr));

    int position[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};

    for (int i = 0; i < 30; i++)
    {
        while (tempDeck->getCard(i) == nullptr)
        {
            int r = rand() % 30;
            if (position[r] == r && r != 0)
            {
                tempDeck->setCardToIndex(deck->getCard(r), i);
                position[r] = r + 1;
            }
        }
    }

    return tempDeck;
}

int Player::getHealth()
{
    return this->health;
}

int Player::getClass()
{
    return this->playClass;
}

std::string Player::getName()
{
    return this->name;
}