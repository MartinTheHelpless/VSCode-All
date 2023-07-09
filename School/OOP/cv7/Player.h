#pragma once
#include <iostream>

class Player
{
private:
    std::string name;
    int coins;
    int score;
    int basePosX;
    int basePosY;

public:
    int posX;
    int posY;

    Player(std::string name);

    void setBasePos(int x, int y);
    void changeName(std::string name);

    void resetStats();
    void incScore(int x);
    void addCoins(int coins);

    std::string getPlayerName();
    int getScore();
    int getCoins();
};
