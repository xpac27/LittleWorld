#include "Direction.h"

Direction::Direction()
{
    PI = 4 * atan(1);
    x  = 1.f;
    y  = 0.f;
}

Direction::Direction(float x, float y)
{
    set(x, y);
}

void Direction::set(Position *from, Position *to)
{
    set(to->x - from->x, to->y - from->y);
}

void Direction::set(float x, float y)
{
    this->x = x;
    this->y = y;

    normalize();
}

void Direction::normalize()
{
    float m = getMagnitude();
    x /= m;
    y /= m;
}

void Direction::setAngle(float a)
{
    a *= PI / 180.f;
    x = cos(a);
    y = sin(a);
}

void Direction::rotate(float delta)
{
    x = (x * cos(delta)) - (y * sin(delta));
    y = (x * sin(delta)) + (y * cos(delta));

    normalize();
}

float Direction::getAngle()
{
    if (y < 0.f)
    {
        return acos(x * -1.f) * (180.f / PI) + 180.f;
    }
    else
    {
        return acos(x) * (180.f / PI);
    }
}

float Direction::getMagnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

float Direction::getX()
{
    return x;
}

float Direction::getY()
{
    return y;
}

