#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
}

void Player::setBasePos(int x, int y)
{
    this->basePosX = x;
    this->basePosY = y;
}

void Player::changeName(std::string name)
{
    this->name = name;
}

void Player::resetStats()
{
    this->score = 0;
    this->posX = this->basePosX;
    this->posX = this->basePosY;
}

void Player::incScore(int x)
{
    this->score += x;
}

void Player::addCoins(int coins)
{
    this->coins += coins;
    this->coins < 0 ? this->coins = 0 : this->coins;
}

std::string Player::getPlayerName()
{
    return this->name;
}

int Player::getScore()
{
    return this->score;
}

int Player::getCoins()
{
    return this->coins;
}