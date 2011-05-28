#ifndef DEF_SEGMENT
#define DEF_SEGMENT

#include "Vector2.h"
#include "../geometry/IntersectionFunctions.h"

#include <vector>
#include <SFML/Graphics.hpp>

class Segment
{
    public:

        Segment(Vector2 p1, Vector2 p2);
        Segment(float x1, float y1, float x2, float y2);

        void translate(Vector2 t);
        void draw();
        void collectIntesectionToSegment(Segment *s, std::vector<Vector2> *pointList);

        Vector2 *getPoint(unsigned int i);

        std::vector<Vector2> *getPoints();


    private:

        std::vector<Vector2> points;
};

#endif

