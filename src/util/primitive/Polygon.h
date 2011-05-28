#ifndef DEF_POLYGON
#define DEF_POLYGON

#include "Vector2.h"
#include "Segment.h"
#include "../geometry/ContainFunctions.h"

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Polygon
{
    public:

        Polygon();

        void translate(Vector2 t);
        void draw();
        void outline();
        void addPoint(Vector2 p);
        void addPoint(float x, float y);
        void computeSegments();
        void clear();

        int getTotalPoint();
        int getTotalSegment();

        bool containsSegment(Segment *s);
        bool containsPosition(Vector2 *p);

        Vector2 *getPoint(unsigned int i);
        Segment *getSegment(unsigned int i);

        std::vector<Vector2> *getPoints();
        std::vector<Segment> *getSegments();


    private:

        std::vector<Vector2> points;
        std::vector<Segment> segments;
};

#endif

