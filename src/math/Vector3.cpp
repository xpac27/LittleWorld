#include "Vector3.h"

const Vector3 Vector3::zero = Vector3(0,0,0);
const Scalar Vector3::Epsilon = std::numeric_limits<int>::epsilon();

Vector3::Vector3()
{
}

Vector3::Vector3(Scalar x, Scalar y, Scalar z)
    : x( x )
    , y( y )
    , z( z )
{
}

Vector3& Vector3::operator+=(const Vector3& vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return *this;
}

Vector3& Vector3::operator*=(Scalar num)
{
    x *= num;
    y *= num;
    z *= num;
    return *this;
}

Vector3& Vector3::operator/=(Scalar num)
{
    this->x /= num;
    this->y /= num;
    this->z /= num;
    return *this;
}

