#ifndef DEF_POINT
#define DEF_POINT

#include "../math/Vector3.h"

#include <vector>
#include <iostream>

class Triangle;

class Point : public Vector3
{
    public:

        Point();
        Point(Vector3 v);
        Point(float x, float y, float z);

        std::vector<Triangle*> sharedTriangles;
};

#endif



