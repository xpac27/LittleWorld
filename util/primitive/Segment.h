#ifndef DEF_SEGMENT
#define DEF_SEGMENT

#include "Vector2.h"
#include "../geometry/IntersectionFunctions.h"

#include <SFML/Graphics.hpp>

class Segment
{
    public:

        Segment();
        Segment(float x1, float y1, float x2, float y2);

        void set(float x1, float y1, float x2, float y2);
        void translate(Vector2 t);
        void draw();
        // TODO rename get to collect
        void getIntesectionToSegment(Segment *s, std::vector<Vector2> *pointList);

        // TODO make getters for points
        // TODO make the above private

        // TODO put this in a vector
        Vector2 p1;
        Vector2 p2;
};

#endif

