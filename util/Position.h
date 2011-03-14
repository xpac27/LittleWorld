#ifndef DEF_UTIL_POSITION
#define DEF_UTIL_POSITION

#include <math.h>

class Position
{
    public:

        Position();
        Position(float x, float y);
        Position(float x, float y, float z);

        void set(float x, float y);
        void set(float x, float y, float z);

        float getDistanceTo(Position *p);

        int getGridX();
        int getGridY();

        float x;
        float y;
        float z;
};

#endif

