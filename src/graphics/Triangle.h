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

        void setCW();
        void setCCW();
        void setTransformationMIN(Vector3 v);
        void setTransformationADD(Vector3 v);
        void setTransformationMUL(float n);
        void setTransformationDIV(float n);
        void resetTransformation();
        void setNormal();
        void setAllVertex();
        void update();

        Vector3 getNormal();

        bool lighted;
        bool cw;
        bool transformed;

        Point* points[3];

        Vector3 pointsTransformed[3];
        Vector3 normalCW;
        Vector3 normalCCW;
};

#endif

