#include "../include/Player.h"
#include "Player.h"

Player::Player()
    : m_X(13.5f), m_Y(23), m_Speed(0.1f), m_State(0), m_Health(3),
      m_Score(0), m_Direction(-1), m_NextDirection(-1) {}

void Player::Update(char map[31][29])
{

    if (m_Direction != m_NextDirection)
        switch (m_NextDirection)
        {
        case 0:
            if (int(10 * m_X) % 10 == 0 && map[int(m_Y) - 1][int(m_X)] != '.' && map[int(m_Y) - 1][int(m_X)] != 'g')
                m_Direction = m_NextDirection;

            break;

        case 1:
            if (int(10 * m_Y) % 10 == 0 && map[int(m_Y)][int(m_X) - 1] != '.' && map[int(m_Y)][int(m_X) - 1] != 'g')
                m_Direction = m_NextDirection;

            break;

        case 2:
            if (int(10 * m_X) % 10 == 0 && map[int(m_Y) + 1][int(m_X)] != '.' && map[int(m_Y) + 1][int(m_X)] != 'g')
                m_Direction = m_NextDirection;

            break;

        case 3:
            if (int(10 * m_Y) % 10 == 0 && map[int(m_Y)][int(m_X) + 1] != '.' && map[int(m_Y)][int(m_X) + 1] != 'g')
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
            m_Y -= m_Speed;

            if (map[int(m_Y)][int(m_X)] == 'x' && int(10 * m_Y) % 10 == 0)
            {
                map[(int)m_Y][(int)m_X] = 'e';
                m_State = 1;
            }
            else if (map[int(m_Y)][int(m_X)] == 'o' && int(10 * m_Y) % 10 == 0)
            {
                m_Score += 10;
                map[(int)m_Y][(int)m_X] = 'e';
            }
        }

        break;

    case 1:
        if (map[(int)m_Y][(int)(m_X - m_Speed)] != '.' && int(10 * m_Y) % 10 == 0)
        {
            m_X -= m_Speed;

            if (map[int(m_Y)][int(m_X)] == 'x' && int(10 * m_X) % 10 == 0)
            {
                map[(int)m_Y][(int)m_X] = 'e';
                m_State = 1;
            }
            else if (map[int(m_Y)][int(m_X)] == 'o' && int(10 * m_X) % 10 == 0)
            {
                m_Score += 10;
                map[(int)m_Y][(int)m_X] = 'e';
            }

            if (m_Y > 14.09f && m_Y < 14.11f && m_X < -1.0f)
                m_X = 28.0f;
        }

        break;

    case 2:

        if (map[(int)ceil(m_Y + m_Speed - 0.1f)][(int)m_X] != '.' && int(10 * m_X) % 10 == 0)
        {
            m_Y += m_Speed;

            if (map[int(m_Y)][int(m_X)] == 'x' && int(10 * m_Y) % 10 == 0)
            {
                map[(int)m_Y][(int)m_X] = 'e';
                m_State = 1;
            }
            else if (map[int(m_Y)][int(m_X)] == 'o' && int(10 * m_Y) % 10 == 0)
            {
                m_Score += 10;
                map[(int)m_Y][(int)m_X] = 'e';
            }
        }

        break;

    case 3:
        if (map[(int)m_Y][(int)ceil(m_X + m_Speed - 0.1f)] != '.' && int(10 * m_Y) % 10 == 0)
        {
            m_X += m_Speed;

            if (map[int(m_Y)][int(m_X)] == 'x' && int(10 * m_X) % 10 == 0)
            {
                map[(int)m_Y][(int)m_X] = 'e';
                m_State = 1;
            }
            else if (map[int(m_Y)][int(m_X)] == 'o' && int(10 * m_X) % 10 == 0)
            {
                m_Score += 10;
                map[(int)m_Y][(int)m_X] = 'e';
            }

            if (m_Y > 14.09f && m_Y < 14.11f && m_X > 28.0f)
                m_X = -1.0f;
        }

        break;

    default:
        break;
    }
}
