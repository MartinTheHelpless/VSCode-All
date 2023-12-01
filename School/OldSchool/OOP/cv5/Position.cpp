#include "Position.h"

Position::Position(long double x, long double y)
{
    this->x = x;
    this->y = y;
}

long double Position::getLng()
{
    return this->x;
}

long double Position::getLat()
{
    return this->y;
}