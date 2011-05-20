#include "ContainFunctions.h"

bool ContainFunctions::PointInQuad(float px, float py, float q1x, float q1y, float q2x, float q2y, float q3x, float q3y, float q4x, float q4y)
{
    // The points creating the polygon.
    float x[4] = {q1x, q2x, q3x, q4x};
    float y[4] = {q1y, q2y, q3y, q4y};

    // How many times the ray crosses a line-segment
    int crossings = 0;

    float x1 = 0;
    float x2 = 0;

    // Iterate through each line
    for (int i = 0; i < 4; i++)
    {
        // This is done to ensure that we get the same result when the line goes from left to right and right to left
        if (x[i] < x[(i+1)%4])
        {
            x1 = x[i];
            x2 = x[(i+1)%4];
        }
        else
        {
            x1 = x[(i+1)%4];
            x2 = x[i];
        }

        // First check if the ray is possible to cross the line
        if (px > x1 && px <= x2 && (py < y[i] || py <= y[(i+1)%4]))
        {
            static const float eps = 0.000001;

            //Calculate the equation of the line
            float dx = x[(i+1)%4] - x[i];
            float dy = y[(i+1)%4] - y[i];
            float k;

            if ( fabs(dx) < eps )
            {
                k = INFINITY;   // math.h
            }
            else
            {
                k = dy/dx;
            }

            float m = y[i] - k * x[i];

            //Find if the ray crosses the line
            float y2 = k * px + m;
            if (py <= y2)
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

