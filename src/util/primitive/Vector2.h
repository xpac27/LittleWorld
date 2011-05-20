#ifndef VECTOR2
#define VECTOR2

#include <cmath>

class Vector2
{
    public:

        float x;
        float y;

        Vector2();
        Vector2(float x, float y);

        Vector2& operator+=(const Vector2& pVector);
        Vector2& operator-=(const Vector2& pVector);
        Vector2& operator*=(float num);
        Vector2& operator/=(float num);

        bool operator!=(const Vector2& vect) const;
        bool operator==(const Vector2& vect) const;

        friend Vector2 operator-(Vector2& vect);
        friend Vector2 operator+(const Vector2& vect1,const Vector2& vect2);
        friend Vector2 operator-(const Vector2& vect1,const Vector2& vect2);
        friend Vector2 operator*(const Vector2& vect1, float value);
        friend Vector2 operator/(const Vector2& vect1, float value);
        friend Vector2 operator*(const Vector2& vect1,const Vector2& vect2);
        friend Vector2 operator/(const Vector2& vect1,const Vector2& vect2);

        static float length(const Vector2& vect);
        static float length2(const Vector2& vect);
        static float dot(const Vector2& pVec1, const Vector2& pVec2);
        static float distance(const Vector2& pVec1, const Vector2& pVec2);

        static Vector2& invert(Vector2& vect);
        static Vector2& normalize(Vector2& vect);
        static Vector2& clamp(Vector2& vect, float value);
        static Vector2& setLength(Vector2& vect, float value);

        static Vector2 polar(float x, float y);
        static Vector2 cartesian(float radius, float angle);
        static Vector2 rotate(const Vector2& pVec, float angle);
};

#endif

