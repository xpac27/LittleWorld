#include "Position.h"

Position::Position()
{
    set(0.f, 0.f, 0.f);
}

Position::Position(float x, float y, float z)
{
    set(x, y, z);
}

void Position::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Position::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Position::getDistanceTo(Position *p)
{
    return sqrt(pow((x - p->x), 2) + pow((y - p->y), 2));
}

