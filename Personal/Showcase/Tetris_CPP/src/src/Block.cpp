#include "../include/Block.h"

int Block::GetX()
{
    return m_X;
}

int Block::GetY()
{
    return m_Y;
}

void Block::SetX(int x)
{
    m_X = x;
}

void Block::SetY(int y)
{
    m_Y = y;
}

void Block::IncrementX()
{
    m_X++;
}

void Block::IncrementY()
{
    m_Y++;
}

void Block::DecrementX()
{
    m_X--;
}

void Block::DecrementY()
{
    m_Y--;
}
