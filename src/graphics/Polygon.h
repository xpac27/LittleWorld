#ifndef DEF_POLYGON
#define DEF_POLYGON

#include "Triangle.h"
#include "../math/Vector3.h"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Polygon
{
    public:

        Polygon();

        void draw();
        void drawOutline();
        void addTriangle(Triangle t);
        void addTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
        void translate(Vector3 t);
        void clear();


    private:

        std::vector<Triangle> triangles;
};

#endif

