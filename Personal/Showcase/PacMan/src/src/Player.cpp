#include "../include/Player.h"
#include "Player.h"

Player::Player()
    : m_X(13.5f), m_Y(23), m_Speed(0.1f)
{
}

void Player::Move(char map[31][29])
{

    if (m_Direction != m_NextDirection)
        switch (m_NextDirection)
        {
        case 0:
            if (int(10 * m_X) % 10 == 0 && map[int(m_Y) - 1][int(m_X)] != '.')
                m_Direction = m_NextDirection;

            break;

        case 1:
            if (int(10 * m_Y) % 10 == 0 && map[int(m_Y)][int(m_X) - 1] != '.')
                m_Direction = m_NextDirection;

            break;

        case 2:
            if (int(10 * m_X) % 10 == 0 && map[int(m_Y) + 1][int(m_X)] != '.')
                m_Direction = m_NextDirection;

            break;

        case 3:
            if (int(10 * m_Y) % 10 == 0 && map[int(m_Y)][int(m_X) + 1] != '.')
                m_Direction = m_NextDirection;

            break;

        default:
            break;
        }

    switch (m_Direction)
    {
    case 0:
        if (map[(int)(m_Y - m_Speed)][(int)m_X] != '.' && int(10 * m_X) % 10 == 0)
        {
            map[(int)m_Y][(int)m_X] = 'e';
            m_Y -= m_Speed;
        }

        break;

    case 1:
        if (map[(int)m_Y][(int)(m_X - m_Speed)] != '.' && int(10 * m_Y) % 10 == 0)
        {
            map[(int)m_Y][(int)m_X] = 'e';
            m_X -= m_Speed;

            if (m_Y > 14.09f && m_Y < 14.11f && m_X < -1.0f)
                m_X = 28.0f;
        }

        break;

    case 2:

        if (map[(int)ceil(m_Y + m_Speed - 0.1f)][(int)m_X] != '.' && int(10 * m_X) % 10 == 0)
        {
            map[(int)m_Y][(int)m_X] = 'e';
            m_Y += m_Speed;
        }

        break;

    case 3:
        if (map[(int)m_Y][(int)ceil(m_X + m_Speed - 0.1f)] != '.' && int(10 * m_Y) % 10 == 0)
        {
            map[(int)m_Y][(int)m_X] = 'e';
            m_X += m_Speed;

            if (m_Y > 14.09f && m_Y < 14.11f && m_X > 28.0f)
                m_X = -1.0f;
        }

        break;

    default:
        break;
    }
}