#ifndef DEF_QUAD
#define DEF_QUAD

#include "Vector2.h"
#include "Segment.h"
#include "ContainFunctions.h"

#include <SFML/Graphics.hpp>

class Quad
{
    public:

        Quad();
        Quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

        void set(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
        void translate(float tx, float ty);
        void draw();
        void outline();

        bool containsSegment(Segment *s);
        bool containsPosition(Vector2 *p);

        // TODO put this in a vector
        Vector2 p1;
        Vector2 p2;
        Vector2 p3;
        Vector2 p4;

        // TODO put this in a vector
        Segment s1;
        Segment s2;
        Segment s3;
        Segment s4;
};

#endif

