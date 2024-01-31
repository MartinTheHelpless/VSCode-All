#pragma once
#include <iostream>
#include <cmath>

class Player
{
private:
    int m_Health;
    int m_Score;
    int m_State; // Powered up and normal
    int m_Direction;
    float m_Speed;
    float m_X; // Coord X
    float m_Y; // Coord Y

public:
    Player();
    ~Player();

    void Move(std::wstring &map);
    void SetMoveDir(int dir) { m_Direction = dir; }

    double GetX() { return m_X; }
    double GetY() { return m_Y; }
};