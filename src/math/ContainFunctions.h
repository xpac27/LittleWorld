#ifndef CONTAINFUNCTIONS
#define CONTAINFUNCTIONS

#include "../graphics/Vector2.h"

#include <cmath>
#include <vector>

class ContainFunctions
{

    public:

        static bool PointInPolygon(Vector2 *p, std::vector<Vector2> *points);
};

#endif


