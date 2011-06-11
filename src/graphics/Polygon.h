#ifndef DEF_POLYGON
#define DEF_POLYGON

#include "Vector2.h"
#include "../math/ContainFunctions.h"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Polygon
{
    public:

        Polygon();

        void draw();
        void outline();
        void addPoint(Vector2 p);
        void addPoint(float x, float y);
        void clear();
        void translate(Vector2 t);

        int getTotalPoint();

        Vector2 *getPoint(unsigned int i);

        std::vector<Vector2> *getPoints();


    private:

        std::vector<Vector2> points;
};

#endif

