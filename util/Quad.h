#ifndef DEF_QUAD
#define DEF_QUAD

#include "Position.h"
#include "Segment.h"
#include "ContainFunctions.h"

#include <vector>
#include <SFML/Graphics.hpp>

class Quad
{
    public:

        Quad();
        Quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

        void set(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
        void draw();
        void outline();

        // TODO put this in a vector
        Position p1;
        Position p2;
        Position p3;
        Position p4;
};

#endif

