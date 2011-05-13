#ifndef INTERSECTIONFUNCTIONS
#define INTERSECTIONFUNCTIONS

#include <vector>
#include <cmath>

#include "Vector2.h"

struct IntersectionObject
{
    std::vector<Vector2> points;

    void InsertSolution(float x, float y)
    {
        points.push_back(Vector2(x, y));
    }

    void InsertSolution(Vector2 v)
    {
        points.push_back(v);
    }

    int NumberOfSolutions()
    {
        return points.size();
    }
};

class IntersectionFunctions
{

    public:

        static IntersectionObject CircleToCircleIntersection(float x0_, float y0_, float r0_, float x1_, float y1_, float r1_);
        static IntersectionObject LineToCircleIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float r3_);
        static IntersectionObject CircleToLineIntersection(float x1_, float y1_, float r1_, float x2_, float y2_, float x3_, float y3_);
        static IntersectionObject LineSegmentToCircleIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float r3_);
        static IntersectionObject CircleToLineSegmentIntersection(float x1_, float y1_, float r1_, float x2_, float y2_, float x3_, float y3_);
        static IntersectionObject RayToCircleIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float r3_);
        static IntersectionObject CircleToRayIntersection(float x1_, float y1_, float r1_, float x2_, float y2_, float x3_, float y3_);
        static IntersectionObject LineToLineIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_);
        static IntersectionObject LineSegmentToLineSegmentIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_);
        static IntersectionObject LineSegmentToLineIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_);
        static IntersectionObject LineToLineSegmentIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_);
        static IntersectionObject RayToLineSegmentIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_);
        static IntersectionObject LineSegmentToRayIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_);
        static IntersectionObject RayToLineIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_);
        static IntersectionObject LineToRayIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_);
        static IntersectionObject RayToRayIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_);
};

#endif

