#ifndef DEF_SEGMENT
#define DEF_SEGMENT

#include "Position.h"

#include <SFML/Graphics.hpp>

class Segment
{
    public:

        Segment();
        Segment(float x1, float y1, float x2, float y2);

        void set(float x1, float y1, float x2, float y2);
        void draw();

        Position p1;
        Position p2;
};

#endif

