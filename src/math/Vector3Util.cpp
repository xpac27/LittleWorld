#include "Vector3Util.h"

void Vector3Util::Clamp(Vector3& vect,Scalar length)
{
    Scalar vecLength = len2(vect);

    if(vecLength <= length * length)
    {
        return;
    }

    vect *= length / sqrt(vecLength);
}

void Vector3Util::Normalize_s(Vector3& vect)
{
    Scalar vecLength = len2(vect);

    if(vecLength == 0)
    {
        return;
    }

    vect /= sqrt(vecLength);
}

void Vector3Util::SetLength_s(Vector3& vect, Scalar length)
{
    Scalar vecLength = len2(vect);

    if(vecLength == 0)
    {
        return;
    }

    vect *= length / sqrt(vecLength);
}

Vector3 Vector3Util::ToNormalized_s(const Vector3& vect)
{
    Scalar vecLength = len2(vect);

    if(vecLength == 0)
    {
        return vect;
    }

    vecLength = sqrt(vecLength);

    return Vector3(vect.x / vecLength, vect.y / vecLength, vect.z / vecLength);
}

// Thanks to Martin Baker for this solution
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToEuler/index.htm
// To Note: I have to debug this to make sure it works as stated.
Vector3 Vector3Util::ToEuler(Vector3 axis, Scalar angle)
{
    Vector3 out = Vector3();

    float W_PI_2 = 3.14f;

    Scalar s = sin(angle);
    Scalar c = cos(angle);
    Scalar t = static_cast<Scalar>(1.0) - c;

    if ((axis.x * axis.y * t + axis.z * s) > static_cast<Scalar>(0.998))// north pole singularity detected
    {
        out.y = static_cast<Scalar>(2.0) * atan2(axis.x * sin(angle / static_cast<Scalar>(2.0)), cos(angle / static_cast<Scalar>(2.0)));
        out.z = static_cast<Scalar>(W_PI_2);
        out.x = 0;
        return out;
    }
    if ((axis.x * axis.y * t + axis.z * s) < static_cast<Scalar>(-0.998))// south pole singularity detected
    {
        out.y = static_cast<Scalar>(-2.0) * atan2(axis.x * sin(angle / static_cast<Scalar>(2.0)), cos(angle / static_cast<Scalar>(2.0)));
        out.z = -static_cast<Scalar>(W_PI_2);
        out.x = 0;
        return out;
    }
    out.y = atan2(axis.y * s - axis.x * axis.z * t , 1 - (axis.y * axis.y + axis.z * axis.z ) * t);
    out.z = asin(axis.x * axis.y * t + axis.z * s) ;
    out.x = atan2(axis.x * s - axis.y * axis.z * t , 1 - (axis.x * axis.x + axis.z * axis.z) * t);
    return out;
}

