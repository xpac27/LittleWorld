#include "Point.h"

Point::Point()
{
    closed = false;
    opened = false;
    walkable = true;
    x = 0;
    y = 0;
    f = 0;
    g = 0;
    h = 0;
}

Point::Point(int x, int y)
{
    closed = false;
    opened = false;
    walkable = true;
    this->x = x;
    this->y = y;
    f = 0;
    g = 0;
    h = 0;
}

Position* Point::getPosition()
{
    return new Position((float)(x * 64), (float)(y * 64));
}

