#ifndef DEF_POLYGON
#define DEF_POLYGON

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
        void drawVertices();
        void addPoint(Vector3 p);
        void addPoint(float x, float y, float z);
        void clear();
        void translate(Vector3 t);

        int getTotalPoint();

        Vector3 *getPoint(unsigned int i);

        std::vector<Vector3> *getPoints();


    private:

        std::vector<Vector3> points;
};

#endif

