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
    int m_NextDirection;
    float m_Speed;
    float m_X; // Coord X
    float m_Y; // Coord Y

public:
    Player();
    ~Player();

    void Move(char map[31][29]);
    void SetMoveDir(int dir) { m_NextDirection = dir; }

    float GetX() { return m_X; }
    float GetY() { return m_Y; }
};