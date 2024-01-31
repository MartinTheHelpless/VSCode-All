#include "../include/Ghost.h"
#include <cmath>
#include "Ghost.h"

Ghost::Ghost(float x, float y, int id, float speed, std::pair<int, int> scatter, SDL_Color color)
    : m_Id(id), m_Speed(speed), m_X(x), m_Y(y), m_ScatterTarget(scatter),
      m_Color(color), m_State(0), m_Direction(3), m_NextDirection(3) {}

void Ghost::Update(char map[31][29])
{

    if (m_Direction != m_NextDirection)
    {
        switch (m_NextDirection)
        {
        case 0:
            if (int(10 * m_X) % 10 <= 1.1f && map[int(m_Y) - 1][int(m_X)] != '.')
                m_Direction = m_NextDirection;

            break;

        case 1:
            if (int(10 * m_Y) % 10 <= 1.1f && map[int(m_Y)][int(m_X) - 1] != '.')
                m_Direction = m_NextDirection;

            break;

        case 2:
            if (int(10 * m_X) % 10 <= 1.1f && map[int(m_Y) + 1][int(m_X)] != '.')
                m_Direction = m_NextDirection;

            break;

        case 3:
            if (int(10 * m_Y) % 10 <= 1.1f && map[int(m_Y)][int(m_X) + 1] != '.')
                m_Direction = m_NextDirection;

            break;

        default:
            break;
        }
    }

    switch (m_Direction)
    {
    case 0:
        if (map[(int)(m_Y - m_Speed)][(int)m_X] != '.' && int(10 * m_X) % 10 <= 1.1f)
            m_Y -= m_Speed;

        break;

    case 1:
        if (map[(int)m_Y][(int)(m_X - m_Speed)] != '.' && int(10 * m_Y) % 10 <= 1.1f)
        {
            m_X -= m_Speed;

            if (m_Y > 14.09f && m_Y < 14.11f && m_X < -1.0f)
                m_X = 28.0f;
        }

        break;

    case 2:

        if (map[(int)ceil(m_Y + m_Speed - 0.1f)][(int)m_X] != '.' && int(10 * m_X) % 10 <= 1.1f)
            m_Y += m_Speed;

        break;

    case 3:
        if (map[(int)m_Y][(int)ceil(m_X + m_Speed - 0.1f)] != '.' && int(10 * m_Y) % 10 <= 1.1f)
        {
            m_X += m_Speed;

            if (m_Y > 14.09f && m_Y < 14.11f && m_X > 28.0f)
                m_X = -1.0f;
        }

        break;

    default:
        break;
    }

    SetNextDirection(map);
}

void Ghost::SetNextDirection(char map[31][29])
{
    switch (m_Direction)
    {

    case 2:
        if (int(ceil(m_Y)) != int(ceil(m_Y + m_Speed)) && map[int(ceil(m_Y + m_Speed))][int(m_X)] != '.')
        {

            float dist = 9999999.0f;
            int dir = 0;

            if (map[int(ceil(m_Y))][int(ceil(m_Y)) + 1] != '.')
            {
                int x = int(m_X) + 1;
                int y = m_Y;

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 3;
                }
            }

            if (map[int(ceil(m_Y)) + 1][int(m_X)] != '.')
            {
                int x = m_X;
                int y = int(ceil(m_Y)) + 1;

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 2;
                }
            }

            if (map[int(m_Y)][int(m_X) - 1] != '.')
            {
                int x = int(m_X) - 1;
                int y = m_Y;

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 1;
                }
            }

            m_NextDirection = dir;
        }
        break;

    case 3:
        if (map[int(m_Y)][int(m_X)] != map[int(m_Y)][int(m_X + m_Speed)] && map[int(m_Y)][int(m_X + m_Speed)] != '.')
        {

            float dist = 1000.0f;
            int dir = 0;

            if (map[int(ceil(m_Y))][int(ceil(m_Y)) + 1] != '.')
            {
                int x = int(m_X) + 1;
                int y = m_Y;

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 3;
                }
            }

            if (map[int(ceil(m_Y)) + 1][int(m_X)] != '.')
            {
                int x = m_X;
                int y = int(ceil(m_Y)) + 1;

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 2;
                }
            }

            if (map[int(m_Y) - 1][int(m_X)] != '.')
            {
                int x = m_X;
                int y = int(m_Y) - 1;

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 0;
                }
            }

            m_NextDirection = dir;
        }
        break;

    default:
        break;
    }
}
