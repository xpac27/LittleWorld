/*  __          __   ___     _____    ____
 *  \ \    / /  / _ \   |  __ \  |    |
 *   \ \/\/ /  / / \ \  | | / /  |  __|
 *    \_/\_/  /_/   \_\ |_| \_\  |_|
 *      Take it to the next Level
 *
 *      Copyright (c) 2009 Brian Ernst.
 */

#ifndef VECTOR3
#define VECTOR3

#include <cmath>
#include <limits>

typedef float   Scalar;
typedef int       Bool;

class Vector3
{
    public:

        Scalar x;
        Scalar y;
        Scalar z;

        Vector3();
        Vector3(Scalar x, Scalar y, Scalar z);

        Vector3     operator+(const Vector3& vector) const;
        Vector3     operator-(const Vector3& vector) const;
        Vector3     operator-() const;
        Vector3     operator*(Scalar num) const;
        Vector3     operator/(Scalar num) const;

        Vector3&    operator+=(const Vector3& vector);
        Vector3&    operator-=(const Vector3& vector);
        Vector3&    operator*=(Scalar num);
        Vector3&    operator/=(Scalar num);

        Bool      operator==(const Vector3& vector) const;
        Bool      operator!=(const Vector3& vector) const;

        static const Vector3 zero;
        static const Scalar   Epsilon;
};

inline Bool Vector3::operator==(const Vector3& vector) const
{
    return x == vector.x && y == vector.y && z == vector.z;
}

inline Bool Vector3::operator!=(const Vector3& vector) const
{
    return x != vector.x || y != vector.y || z != vector.z;
}

inline Vector3 Vector3::operator+(const Vector3& vector) const
{
    return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

inline Vector3 Vector3::operator-(const Vector3& vector) const
{
    return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

inline Vector3 Vector3::operator-() const
{
    return Vector3(-x,-y,-z);
}

inline Vector3 Vector3::operator*(Scalar num) const
{
    return Vector3(x * num, y * num, z * num);
}

inline Vector3 Vector3::operator/(Scalar num) const
{
    return Vector3(x / num, y / num, z / num);
}

#endif

