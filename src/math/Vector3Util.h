/*  __          __   ___     _____    ____
 *  \ \    / /  / _ \   |  __ \  |    |
 *   \ \/\/ /  / / \ \  | | / /  |  __|
 *    \_/\_/  /_/   \_\ |_| \_\  |_|
 *      Take it to the next Level
 *
 *      Copyright (c) 2009 Brian Ernst.
 */

#ifndef VECTOR3UTIL
#define VECTOR3UTIL

#include "Vector3.h"

// These two files are not detailed out in this blog post.
//#include "Quaternion.h"
//#include "TMatrixUtil.h"

class Vector3Util
{
    public:

        static Scalar len(const Vector3& vect);
        static Scalar len2(const Vector3& vect);
        static Scalar dist(const Vector3& from, const Vector3& to);

        static void Clamp(Vector3& vect,Scalar length);
        static void Normalize(Vector3& vect);
        static void Normalize_s(Vector3& vect);
        static void SetLength(Vector3& vect, Scalar length);
        static void SetLength_s(Vector3& vect, Scalar length);

        static Scalar Dot(const Vector3& vec1, const Vector3& vec2);

        static Vector3 ToNormalized(const Vector3& vect);
        static Vector3 ToNormalized_s(const Vector3& vect);
        static Vector3 ToPolar(Scalar x, Scalar y, Scalar z);
        static Vector3 ToCartesian(Scalar radius, Scalar angle, Scalar z);
        static Vector3 Cross(const Vector3& vec1, const Vector3& vec2);
        static Vector3 Rotate(const Vector3& vec1, Scalar angle, const Vector3& axis);

        static Vector3 ToEuler(Vector3 axis, Scalar angle);
};

inline Scalar Vector3Util::len(const Vector3& vect)
{
    return sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
}

inline Scalar Vector3Util::len2(const Vector3& vect)
{
    return vect.x * vect.x + vect.y * vect.y + vect.z * vect.z;
}

inline Scalar Vector3Util::dist(const Vector3& from, const Vector3& to)
{
    return sqrt(pow(from.x - to.x, 2) + pow(from.y - to.y, 2) + pow(from.z - to.z, 2));
}

inline void Vector3Util::Normalize(Vector3& vect)
{
    vect /= len(vect);
}

inline void Vector3Util::SetLength(Vector3& vect, Scalar length)
{
    vect *= length / len(vect);
}

inline Scalar Vector3Util::Dot(const Vector3& vec1, const Vector3& vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

inline Vector3 Vector3Util::ToNormalized(const Vector3& vect)
{
    return vect / len(vect);
}

// This uses a Quaternion combined with the Matrix Utility, neither of which are detailed out in this post.
//inline Vector3  Rotate(const Vector3& vec1, Scalar angle, const Vector3& axis)
//{
    //return TransformCoord(Quaternion::FromAxis(axis.x,axis.y,axis.z,angle).Get_RotationMatrix(),vec1);
//}

inline Vector3 Vector3Util::ToPolar(Scalar x, Scalar y, Scalar z)
{
    return Vector3(
        atan2(y,x),
        sqrt(x * x + y * y),
        z);
}

inline Vector3 Vector3Util::ToCartesian(Scalar radius, Scalar angle, Scalar z)
{
    return Vector3(
        radius * cos(angle),
        radius * sin(angle),
        z);
}

inline Vector3 Vector3Util::Cross(const Vector3& vec1, const Vector3& vec2)
{
    return Vector3(
        vec1.y * vec2.z - vec1.z * vec2.y,
        vec1.z * vec2.x - vec1.x * vec2.z,
        vec1.x * vec2.y - vec1.y * vec2.x);
}

#endif

