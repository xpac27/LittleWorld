#ifndef DEF_TRIANGLE
#define DEF_TRIANGLE

#include "../math/Vector3.h"
#include "../math/Vector3Util.h"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Triangle
{
    public:

        Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

        void draw();
        void drawOutline();
        void drawVertices();
        void translate(Vector3 t);


    private:

        Vector3 points[3];
        Vector3 normal;
};

#endif


