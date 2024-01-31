#include "../include/Player.h"
#include "Player.h"

Player::Player()
    : m_X(1), m_Y(1), m_Speed(0.1f)
{
}

void Player::Move(std::wstring &map)
{
    switch (m_Direction)
    {
    case 0:
        if (map[(m_Y - m_Speed) * 28 + m_X] != '.')
            m_Y -= m_Speed;

        break;

    case 1:
        if (map[m_Y * 28 + (m_X - m_Speed)] != '.')
            m_X -= m_Speed;

        break;

    case 2:

        if (map[(m_Y + m_Speed) * 28 + m_X] != '.')
            m_Y += m_Speed;

        break;

    case 3:
        if (map[m_Y * 28 + (m_X + m_Speed)] != '.')
            m_X += m_Speed;

        break;

    default:
        break;
    }
}