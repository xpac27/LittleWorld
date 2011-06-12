#ifndef DEF_POLYGON
#define DEF_POLYGON

#include "Point.h"
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
        void drawShadow(Vector3 lightPosition);
        void addTriangle(Point *p1, Point *p2, Point *p3);
        void clear();
        void updateConnectivity();
        void updateShadows(Vector3 lightPosition);


    private:

        std::vector<Triangle> triangles; // rename to shapeVolume
        std::vector<Point*> silhouette;
};

#endif

