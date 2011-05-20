#ifndef DEF_UTIL_POINT
#define DEF_UTIL_POINT

#include "primitive/Vector2.h"

#include <cstdlib>
#include <iostream>

// TODO Rename to Block

class Point
{
    public:

        Point();
        Point(int x, int y, bool w);

        Vector2* getPosition();
        Point* getParent();

        void setParent(Point *p);
        void computeScores(Point *end);

        int getX();
        int getY();
        int getGScore(Point *p);
        int getHScore(Point *p);
        int getGScore();
        int getHScore();
        int getFScore();

        float getXf();
        float getYf();

        bool hasParent();

        bool walkable;
        bool closed;
        bool opened;


    private :

        int x;
        int y;

        unsigned int f;
        unsigned int g;
        unsigned int h;

        Point *parent;
};

#endif

