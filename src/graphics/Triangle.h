#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "Point.h"
#include "../math/Vector3.h"
#include "../math/Vector3Util.h"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Triangle
{
    public:

        Triangle(Point *p1, Point *p2, Point *p3);

        void draw();
        void drawOutline();
        void drawVertices();
        void update();

        bool lighted;

        Point* points[3];

        Vector3 normal;
};

#endif

