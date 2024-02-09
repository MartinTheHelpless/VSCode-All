#include "../include/Ghost.h"
#include <cmath>
#include <vector>

Ghost::Ghost(int id, float x, float y, int direction, float speed, std::pair<int, int> scatter, SDL_Color color)
    : m_ID(id), m_Speed(speed), m_X(x), m_Y(y), m_ScatterTarget(scatter), m_Color(color), m_FrameMove(0.05f),
      m_Direction(direction), m_NextDirection(direction), m_State(0), m_ScaredStartTicks(0) {}

void Ghost::Update(char map[31][29], int pacManX, int pacManY, int pacManDir, int blinkyX, int blinkyY, Uint32 ticks)
{

    m_X = float(int(m_X * 1000.0f) / 1000.0f);
    m_Y = float(int(m_Y * 1000.0f) / 1000.0f);

    for (int i = 0; i < m_Speed; i++)
    {
        if (m_State != 2)
        {
            ChangeDirectionIfOnCrossroad(pacManX, pacManY, pacManDir, blinkyX, blinkyY, map);
            SetNextDirection(map);
        }
        else
        {
        }

        UpdateState(ticks, map);
    }
}

void Ghost::ChangeDirectionIfOnCrossroad(int pacManX, int pacManY, int pacManDir, int blinkyX, int blinkyY, char map[31][29])
{

    switch (m_Direction)
    {
    case 0:
        if (map[int(m_Y - m_FrameMove * 2)][int(m_X)] != '.' && int(10 * m_X) % 10 <= m_FrameMove * 2 * 11.0f)
        {
            m_Y -= m_FrameMove;

            ChangeDirection(map);

            m_ChaseTarget = GetChaseTile(m_ID, pacManX, pacManY, pacManDir, blinkyX, blinkyY);
        }
        break;

    case 1:
        if (map[(int)m_Y][(int)(m_X - m_FrameMove * 2)] != '.' && int(10 * m_Y) % 10 <= m_FrameMove * 2 * 11.0f)
        {
            m_X -= m_FrameMove;

            if (m_Y > 14.0f && m_Y < 14.3f && m_X < -0.5f)
                m_X = 27.0f;

            ChangeDirection(map);

            m_ChaseTarget = GetChaseTile(m_ID, pacManX, pacManY, pacManDir, blinkyX, blinkyY);
        }

        break;

    case 2:

        if (map[(int)ceil(m_Y + m_FrameMove * 2 - 0.1f)][(int)m_X] != '.' && int(10 * m_X) % 10 <= m_FrameMove * 2 * 11.0f)
        {
            m_Y += m_FrameMove;

            ChangeDirection(map);

            m_ChaseTarget = GetChaseTile(m_ID, pacManX, pacManY, pacManDir, blinkyX, blinkyY);
        }
        break;

    case 3:
        if (map[(int)m_Y][(int)ceil(m_X + m_FrameMove * 2 - 0.1f)] != '.' && int(10 * m_Y) % 10 <= m_FrameMove * 2 * 11.0f)
        {
            m_X += m_FrameMove;

            if (m_Y > 14.0f && m_Y < 14.3f && m_X > 27.0f)
                m_X = -0.5f;

            ChangeDirection(map);

            m_ChaseTarget = GetChaseTile(m_ID, pacManX, pacManY, pacManDir, blinkyX, blinkyY);
        }
        break;

    default:
        break;
    }
}

void Ghost::UpdateState(Uint32 ticks, char map[31][29])
{

    if (m_State == 0 || m_State == 1)
    {
        int total = m_ChangeTimes[0];
        int i = 1;

        while ((ticks / 1000.0f) > total)
            total += m_ChangeTimes[i++];

        i > 0 ? i-- : i;

        if (i % 2 != m_State)
        {
            SetState(i % 2);
            SetNextDirection(map);
        }
    }
    else if (m_State == 2)
    {

        if (m_ScaredStartTicks / 1000.0f + 6 <= SDL_GetTicks() / 1000.0f)
        {
            SetState(0);
            SetNextDirection(map);
        }
    }
}

void Ghost::SetNextDirection(char map[31][29])
{

    std::pair<int, int> target;

    switch (m_State)
    {
    case 0:
        target = m_ScatterTarget;
        break;

    case 1:
        target = m_ChaseTarget;
        break;

    case 3:
        if (int(m_X) == 14 && int(m_Y) == 15)
        {
            SetState(0);
            m_Direction = 2;
            m_NextDirection = 0;
            target = m_ScatterTarget;

            break;
        }
        else
            target = {14, 15}; // Ghost house coords
        break;

    default:
        break;
    }

    GetNextDirection(target, map);
}

std::pair<int, int> Ghost::GetChaseTile(int ghostID, int pacManX, int pacManY, int pacManDir, int blinkyX, int blinkyY)
{

    std::pair<int, int> target;

    switch (ghostID)
    {
    case 0: // Blinky
    {
        target = {pacManX, pacManY};
        break;
    }
    case 1: // Pinky
    {
        switch (pacManDir)
        {
        case 0:
            target = {pacManX - 4, pacManY - 4};
            break;

        case 1:
            target = {pacManX - 4, pacManY};

            break;

        case 2:
            target = {pacManX, pacManY + 4};

            break;

        case 3:
            target = {pacManX + 4, pacManY};

            break;

        default:
            break;
        }

        break;
    }
    case 2: // Inky
    {

        int x, y;

        switch (pacManDir)
        {
        case 0:

            if (blinkyX > pacManX)
                x = pacManX - 2 - abs(pacManX - blinkyX);
            else
                x = pacManX - 2 + abs(pacManX - blinkyX);

            if (blinkyY > pacManY)
                y = pacManY - 2 - abs(pacManY - blinkyY);
            else
                y = pacManY - 2 + abs(pacManY - blinkyY);

            target = {x, y};
            break;

        case 1:

            if (blinkyX > pacManX)
                x = pacManX - 2 - abs(pacManX - blinkyX);
            else
                x = pacManX - 2 + abs(pacManX - blinkyX);

            if (blinkyY > pacManY)
                y = pacManY - abs(blinkyY - pacManY);
            else
                y = pacManY + abs(pacManY - blinkyY);

            target = {x, y};
            break;

        case 2:

            if (blinkyX > pacManX)
                x = pacManX - abs(blinkyX - pacManX);
            else
                x = pacManX + abs(pacManX - blinkyX);

            if (blinkyY > pacManY)
                y = pacManY + 2 - abs(pacManY - blinkyY);
            else
                y = pacManY + 2 + abs(pacManY - blinkyY);

            target = {x, y};
            break;

        case 3:

            if (blinkyX > pacManX)
                x = pacManX + 2 - abs(blinkyX - pacManX);
            else
                x = pacManX + 2 + abs(pacManX - blinkyX);

            if (blinkyY > pacManY)
                y = pacManY - abs(pacManY - blinkyY);
            else
                y = pacManY + abs(pacManY - blinkyY);

            target = {x, y};
            break;

        default:
            break;
        }

        break;
    }
    case 3: // Clyde
    {
        int x = pacManX - m_X;
        int y = pacManY - m_Y;
        float dist = sqrt(x * x + y * y);

        if (dist < 8)
            target = m_ScatterTarget;
        else
            target = {pacManX, pacManY};

        break;
    }

    default:
        break;
    }

    return target;
}

void Ghost::GetNextDirection(std::pair<int, int> &target, char map[31][29])
{

    switch (m_Direction)
    {
    case 0:
    {
        if (int(m_Y) != int(m_Y - m_FrameMove * 2) && map[int(m_Y - m_FrameMove * 2)][int(m_X)] != '.')
            m_NextDirection = GetFreeDirection(int(m_X), int(m_Y - m_FrameMove * 2), target, map);
        break;
    }

    case 1:
    {
        if (int(m_X) != int(m_X - m_FrameMove * 2) && map[int(m_Y)][int(m_X - m_FrameMove * 2)] != '.')
            m_NextDirection = GetFreeDirection(int(m_X - m_FrameMove * 2), int(m_Y), target, map);
        break;
    }

    case 2:
    {
        if (int(m_Y) != int(m_Y + m_FrameMove * 2) && map[int(m_Y + m_FrameMove * 2)][int(m_X)] != '.')
            m_NextDirection = GetFreeDirection(int(m_X), int(m_Y + m_FrameMove * 2), target, map);
        break;
    }

    case 3:
    {
        if (int(m_X) != int(m_X + m_FrameMove * 2) && map[int(m_Y)][int(m_X + m_FrameMove * 2)] != '.')
            m_NextDirection = GetFreeDirection(int(m_X + m_FrameMove * 2), int(m_Y), target, map);
    }
    break;

    default:
        break;
    }
}

int Ghost::GetFreeDirection(int base_X, int base_Y, std::pair<int, int> &target, char map[31][29])
{

    float dist = FLOAT_MAX;
    int dir = 3;

    if (m_Direction != 1 && map[base_Y][base_X + 1] != '.')
    {
        int x = base_X + 1;
        int y = base_Y;

        float vec = sqrt((target.first - x) * (target.first - x) + (target.second - y) * (target.second - y));

        if (vec <= dist)
        {
            dist = vec;
            dir = 3;
        }
    }

    if (m_Direction != 0 && map[base_Y + 1][base_X] != '.')
    {

        int x = base_X;
        int y = base_Y + 1;

        float vec = sqrt((target.first - x) * (target.first - x) + (target.second - y) * (target.second - y));

        if (vec <= dist)
        {
            dist = vec;
            dir = 2;
        }
    }

    if (m_Direction != 3 && map[base_Y][base_X - 1] != '.')
    {
        int x = base_X - 1;
        int y = base_Y;

        float vec = sqrt((target.first - x) * (target.first - x) + (target.second - y) * (target.second - y));

        if (vec <= dist)
        {
            dist = vec;
            dir = 1;
        }
    }

    if (m_Direction != 2 && map[base_Y - 1][base_X] != '.')
    {

        int x = base_X;
        int y = base_Y - 1;

        float vec = sqrt((target.first - x) * (target.first - x) + (target.second - y) * (target.second - y));

        if (vec <= dist)
        {
            dist = vec;
            dir = 0;
        }
    }

    return dir;
}

int Ghost::GetRandomFreeDirection(int base_X, int base_Y, char map[31][29])
{

    std::vector<int> dirs;

    if (m_Direction != 2 && map[base_Y - 1][base_X] != '.')
        dirs.push_back(0);

    if (m_Direction != 3 && map[base_Y][base_X - 1] != '.')
        dirs.push_back(1);

    if (m_Direction != 0 && map[base_Y + 1][base_X] != '.')
        dirs.push_back(2);

    if (m_Direction != 1 && map[base_Y][base_X + 1] != '.')
        dirs.push_back(3);

    return dirs[rand() % dirs.size()];
}

void Ghost::ChangeDirection(char map[31][29])
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
}
