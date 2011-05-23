#include "ContainFunctions.h"

using namespace std;

bool ContainFunctions::PointInPolygon(Vector2 *p, vector<Vector2> *points)
{
    // How many times the ray crosses a line-segment
    int crossings = 0;

    const unsigned int s = points->size();

    float x1 = 0;
    float x2 = 0;

    // Iterate through each line
    for (int i = 0; i < s; i++)
    {
        // This is done to ensure that we get the same result when the line goes from left to right and right to left
        if (points->at(i).x < points->at((i+1)%s).x)
        {
            x1 = points->at(i).x;
            x2 = points->at((i+1)%s).x;
        }
        else
        {
            x1 = points->at((i+1)%s).x;
            x2 = points->at(i).x;
        }

        // First check if the ray is possible to cross the line
        if (p->x > x1 && p->x <= x2 && (p->y < points->at(i).y || p->y <= points->at((i+1)%s).y))
        {
            static const float eps = 0.000001;

            //Calculate the equation of the line
            float dx = points->at((i+1)%s).x - points->at(i).x;
            float dy = points->at((i+1)%s).y - points->at(i).y;
            float k;

            if ( fabs(dx) < eps )
            {
                k = INFINITY;   // math.h
            }
            else
            {
                k = dy/dx;
            }

            float m = points->at(i).y - k * points->at(i).x;

            //Find if the ray crosses the line
            float y2 = k * p->x + m;
            if (p->y <= y2)
            {
                crossings++;
            }
        }
    }

    if (crossings % 2 == 1)
    {
        return true;
    }
    return false;
}

