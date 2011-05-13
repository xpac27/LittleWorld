#include "Vector2.h"

// TODO put all functions inline

Vector2::Vector2()
{
}

Vector2::Vector2(float x,float y) : x( x ), y( y )
{
}

bool Vector2::operator!=(const Vector2& vector) const
{
    return x != vector.x || y != vector.y;
}

bool Vector2::operator==(const Vector2& vect) const
{
    return (*this != vect) == false;
}

Vector2& Vector2::operator+=(const Vector2& pVector)
{
    x += pVector.x;
    y += pVector.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& pVector)
{
    x -= pVector.x;
    y -= pVector.y;
    return *this;
}

Vector2& Vector2::operator*=(float num)
{
    x *= num;
    y *= num;
    return *this;
}

Vector2& Vector2::operator/=(float num)
{
    x /= num;
    y /= num;
    return *this;
}

Vector2 operator+(const Vector2& vect1,const Vector2& vect2)
{
    return Vector2(vect1.x + vect2.x,vect1.y + vect2.y);
}

Vector2 operator-(const Vector2& vect1,const Vector2& vect2)
{
    return Vector2(vect1.x - vect2.x,vect1.y - vect2.y);
}

Vector2 operator-(Vector2& vect)
{
    return vect * -1;
}

Vector2 operator*(const Vector2& vect1, float value)
{
    return Vector2(vect1.x * value,vect1.y * value);
}

Vector2 operator/(const Vector2& vect1, float value)
{
    return Vector2(vect1.x / value,vect1.y / value);
}

Vector2 operator*(const Vector2& vect1,const Vector2& vect2)
{
    return Vector2(vect1.x * vect2.x,vect1.y * vect2.y);
}

Vector2 operator/(const Vector2& vect1,const Vector2& vect2)
{
    return Vector2(vect1.x / vect2.x,vect1.y / vect2.y);
}
float Vector2::length(const Vector2& vect)
{
    return sqrt(vect.x * vect.x + vect.y * vect.y);
}

float Vector2::length2(const Vector2& vect)
{
    return vect.x * vect.x + vect.y * vect.y;
}

float Vector2::dot(const Vector2& pVec1,const Vector2& pVec2)
{
    return pVec1.x * pVec2.x + pVec1.y * pVec2.y;
}

Vector2& Vector2::invert(Vector2& vect)
{
    return vect *= -1;
}

Vector2& Vector2::normalize(Vector2& vect)
{
    if(vect.x == 0 && vect.y == 0)
    {
        return vect;
    }

    float l = length(vect);

    vect.x /= l;
    vect.y /= l;
    return vect;
}

Vector2& Vector2::clamp(Vector2& vect,float value)
{
    float l = length2(vect);
    if(l <= value * value)
    {
        return vect;
    }

    l = sqrt(l);

    vect.x *= value / l;
    vect.y *= value / l;

    return vect;
}

Vector2& Vector2::setLength(Vector2& vect, float value)
{
    if(vect.x == 0 && vect.y == 0)
    {
        return vect;
    }

    float l = length(vect);

    vect.x *= value / l;
    vect.y *= value / l;

    return vect;
}

Vector2 Vector2::cartesian(float radius,float angle)
{
    return Vector2(radius * cos(angle),radius * sin(angle));
}

Vector2 Vector2::polar(float x,float y)
{
    return Vector2(atan2(y,x),sqrt(x * x + y * y));
}

Vector2 Vector2::rotate(const Vector2& pVec,float angle)
{
    float cosResult = cos(angle);
    float sinResult = sin(angle);

    //Essentially, apply a 2x2 rotation matrix to the vector
    float newx = pVec.x * cosResult - pVec.y * sinResult;
    float newy = pVec.x * sinResult + pVec.y * cosResult;

    return Vector2(newx,newy);
}

