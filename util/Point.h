#ifndef DEF_UTIL_POINT
#define DEF_UTIL_POINT

#include "Position.h"

class Point
{
    public:

        Point();
        Point(int x, int y);

        Position* getPosition();

        int x;
        int y;

        unsigned int f;
        unsigned int g;
        unsigned int h;

        bool walkable;
        bool closed;
        bool opened;

        Point *parent;
};

#endif

