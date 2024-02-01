#include "../include/Ghost.h"
#include <cmath>
#include "Ghost.h"

#define FLOAT_MAX 3.40282e+038

Ghost::Ghost(float x, float y, int direction, float speed, std::pair<int, int> scatter, SDL_Color color)
    : m_Speed(speed), m_X(x), m_Y(y), m_ScatterTarget(scatter),
      m_Color(color), m_State(0), m_Direction(direction), m_NextDirection(direction) {}

void Ghost::Update(char map[31][29])
{

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

    SetNextDirection(map);
}

void Ghost::SetNextDirection(char map[31][29])
{
    switch (m_Direction)
    {
    case 0:
        if (int(m_Y) != int(m_Y - m_Speed) && map[int(m_Y - m_Speed)][int(m_X)] != '.')
        {

            float dist = FLOAT_MAX;
            int dir = 0;

            if (map[int(m_Y - m_Speed)][int(m_X) + 1] != '.')
            {
                int x = int(m_X) + 1;
                int y = int(m_Y - m_Speed);

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 3;
                }
            }

            if (map[int(m_Y - m_Speed)][int(m_X) - 1] != '.')
            {
                int x = int(m_X) - 1;
                int y = int(m_Y - m_Speed);

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 1;
                }
            }

            if (map[int(m_Y - m_Speed) - 1][int(m_X)] != '.')
            {

                int x = m_X;
                int y = int(m_Y - m_Speed) - 1;

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

    case 1:
        if (int(m_X) != int(m_X - m_Speed) && map[int(m_Y)][int(m_X - m_Speed)] != '.')
        {

            float dist = FLOAT_MAX;
            int dir = 0;

            if (map[int(m_Y) + 1][int(m_X - m_Speed)] != '.')
            {

                int x = int(m_X - m_Speed);
                int y = int(m_Y) + 1;

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 2;
                }
            }

            if (map[int(m_Y)][int(m_X - m_Speed) - 1] != '.')
            {
                int x = int(m_X - m_Speed) - 1;
                int y = int(m_Y);

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 1;
                }
            }

            if (map[int(m_Y) - 1][int(m_X - m_Speed)] != '.')
            {

                int x = int(m_X - m_Speed);
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

    case 2:
        if (int(m_Y) != int(m_Y + m_Speed) && map[int(m_Y + m_Speed)][int(m_X)] != '.')
        {

            float dist = FLOAT_MAX;
            int dir = 2;

            if (map[int(m_Y + m_Speed)][int(m_X) + 1] != '.')
            {
                int x = int(m_X) + 1;
                int y = int(m_Y + m_Speed);

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 3;
                }
            }

            if (map[int(m_Y + m_Speed) + 1][int(m_X)] != '.')
            {

                int x = m_X;
                int y = int(m_Y + m_Speed) + 1;

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 2;
                }
            }

            if (map[int(m_Y + m_Speed)][int(m_X) - 1] != '.')
            {
                int x = int(m_X) - 1;
                int y = int(m_Y + m_Speed);

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
        if (int(m_X) != int(m_X + m_Speed) && map[int(m_Y)][int(m_X + m_Speed)] != '.')
        {

            float dist = FLOAT_MAX;
            int dir = 0;

            if (map[int(m_Y)][int(m_X + m_Speed) + 1] != '.')
            {
                int x = int(m_X + m_Speed) + 1;
                int y = int(m_Y);

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 3;
                }
            }

            if (map[int(m_Y) + 1][int(m_X + m_Speed)] != '.')
            {

                int x = int(m_X + m_Speed);
                int y = int(m_Y) + 1;

                float vec = sqrt((m_ScatterTarget.first - x) * (m_ScatterTarget.first - x) + (m_ScatterTarget.second - y) * (m_ScatterTarget.second - y));

                if (vec <= dist)
                {
                    dist = vec;
                    dir = 2;
                }
            }

            if (map[int(m_Y) - 1][int(m_X + m_Speed)] != '.')
            {

                int x = int(m_X + m_Speed);
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
