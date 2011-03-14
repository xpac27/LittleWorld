#ifndef DEF_UTIL_DIRECTION
#define DEF_UTIL_DIRECTION

#include <math.h>
#include "Position.h"

class Direction
{
    public:

        Direction();
        Direction(float x, float y);

        void set(float x, float y);
        void set(Position *from, Position *to);
        void normalize();
        void setAngle(float a);
        void rotate(float delta);

        float getX();
        float getY();
        float getAngle();
        float getMagnitude();


    private:

        float x;
        float y;
        float PI;
};

#endif

