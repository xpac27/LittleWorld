#ifndef DEF_UTIL_POSITION
#define DEF_UTIL_POSITION

#include <math.h>

// TODO Replace by Vector2

class Position
{
    public:

        Position();
        Position(float x, float y);
        Position(float x, float y, float z);

        void set(float x, float y);
        void set(float x, float y, float z);
        void translate(float tx, float ty);

        float getDistanceTo(Position *p);

        int getGridX();
        int getGridY();

        float x;
        float y;
        float z;

        unsigned int f;
        unsigned int g;
        unsigned int h;
};

#endif

