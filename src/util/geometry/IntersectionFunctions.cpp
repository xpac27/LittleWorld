#include "IntersectionFunctions.h"

// Circle to Circle
IntersectionObject IntersectionFunctions::CircleToCircleIntersection(float x0_, float y0_, float r0_, float x1_, float y1_, float r1_)
{
    IntersectionObject result;
    float a, dist, h;
    Vector2 d, r, v2;

    // d is the vertical and horizontal distances between the circle centers
    d = Vector2(x1_ - x0_, y1_ - y0_);

    //distance between the circles
    dist = Vector2::length2(d);

    // Check for equality and infinite intersections exist
    if (dist == 0 && r0_ == r1_)
    {
        return result;
    }

    //Check for solvability
    if (dist > r0_ + r1_)
    {
        // no solution. circles do not intersect
        return result;
    }
    if (dist < abs(r0_ - r1_))
    {
        // no solution. one circle is contained in the other
        return result;
    }
    if (dist == r0_ + r1_)
    {
        //one solution
        result.InsertSolution((x0_ - x1_) / (r0_ + r1_) * r0_ + x1_, (y0_ - y1_) / (r0_ + r1_) * r0_ + y1_);
        return result;
    }

    /* 'point 2' is the point where the line through the circle
        * intersection points crosses the line between the circle
        * centers.
        */

    // Determine the distance from point 0 to point 2
    a = ((r0_ * r0_) - (r1_ * r1_) + (dist * dist)) / (2.0f * dist);

    // Determine the coordinates of point 2
    v2 = Vector2(x0_ + (d.x * a / dist), y0_ + (d.y * a / dist));

    // Determine the distance from point 2 to either of the intersection points
    h = sqrt((r0_ * r0_) - (a * a));

    // Now determine the offsets of the intersection points from point 2
    r = Vector2(-d.y * (h / dist), d.x * (h / dist));

    // Determine the absolute intersection points
    result.InsertSolution(v2 + r);
    result.InsertSolution(v2 - r);

    return result;
}

//Line to Circle
IntersectionObject IntersectionFunctions::LineToCircleIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float r3_)
{
    IntersectionObject result;
    Vector2 v1, v2;
    // Vector from point 1 to point 2
    v1 = Vector2(x2_ - x1_, y2_ - y1_);
    // Vector from point 1 to the circle's center
    v2 = Vector2(x3_ - x1_, y3_ - y1_);

    float dot = v1.x * v2.x + v1.y * v2.y;
    Vector2 proj1 = Vector2(((dot / (Vector2::length(v1))) * v1.x), ((dot / (Vector2::length(v1))) * v1.y));
    Vector2 midpt = Vector2(x1_ + proj1.x, y1_ + proj1.y);

    float distToCenter = (midpt.x - x3_) * (midpt.x - x3_) + (midpt.y - y3_) * (midpt.y - y3_);
    if (distToCenter > r3_ * r3_) return result;
    if (distToCenter == r3_ * r3_)
    {
        result.InsertSolution(midpt);
        return result;
    }
    float distToIntersection;
    if (distToCenter == 0)
    {
        distToIntersection = r3_;
    }
    else
    {
        distToCenter = sqrt(distToCenter);
        distToIntersection = sqrt(r3_ * r3_ - distToCenter * distToCenter);
    }
    float lineSegmentLength = 1 / Vector2::length2(v1);
    v1 *= lineSegmentLength;
    v1 *= distToIntersection;

    result.InsertSolution(midpt + v1);
    result.InsertSolution(midpt - v1);

    return result;
}

// Circle to Line
IntersectionObject IntersectionFunctions::CircleToLineIntersection(float x1_, float y1_, float r1_, float x2_, float y2_, float x3_, float y3_)
{
    return LineToCircleIntersection(x2_, y2_, x3_, y3_, x1_, y1_, r1_);
}

// LineSegment to Circle
IntersectionObject IntersectionFunctions::LineSegmentToCircleIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float r3_)
{
    IntersectionObject result;
    Vector2 v1, v2;
    // Vector from point 1 to point 2
    v1 = Vector2(x2_ - x1_, y2_ - y1_);
    // Vector from point 1 to the circle's center
    v2 = Vector2(x3_ - x1_, y3_ - y1_);

    float dot = v1.x * v2.x + v1.y * v2.y;
    Vector2 proj1 = Vector2(((dot / (Vector2::length(v1))) * v1.x), ((dot / (Vector2::length(v1))) * v1.y));

    Vector2 midpt = Vector2(x1_ + proj1.x, y1_ + proj1.y);
    float distToCenter = (midpt.x - x3_) * (midpt.x - x3_) + (midpt.y - y3_) * (midpt.y - y3_);
    if (distToCenter > r3_ * r3_) return result;
    if (distToCenter == r3_ * r3_)
    {
        result.InsertSolution(midpt);
        return result;
    }
    float distToIntersection;
    if (distToCenter == 0)
    {
        distToIntersection = r3_;
    }
    else
    {
        distToCenter = sqrt(distToCenter);
        distToIntersection = sqrt(r3_ * r3_ - distToCenter * distToCenter);
    }
    float lineSegmentLength = 1 / Vector2::length2(v1);
    v1 *= lineSegmentLength;
    v1 *= distToIntersection;

    Vector2 solution1 = midpt + v1;
    if ((solution1.x - x1_) * v1.x + (solution1.y - y1_) * v1.y > 0 &&
        (solution1.x - x2_) * v1.x + (solution1.y - y2_) * v1.y < 0)
    {
        result.InsertSolution(solution1);
    }
    Vector2 solution2 = midpt - v1;
    if ((solution2.x - x1_) * v1.x + (solution2.y - y1_) * v1.y > 0 &&
        (solution2.x - x2_) * v1.x + (solution2.y - y2_) * v1.y < 0)
    {
        result.InsertSolution(solution2);
    }
    return result;
}

// Circle to LineSegment
IntersectionObject IntersectionFunctions::CircleToLineSegmentIntersection(float x1_, float y1_, float r1_, float x2_, float y2_, float x3_, float y3_)
{
    return LineSegmentToCircleIntersection(x2_, y2_, x3_, y3_, x1_, y1_, r1_);
}

// Ray to Circle
IntersectionObject IntersectionFunctions::RayToCircleIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float r3_)
{
    IntersectionObject result;
    Vector2 v1, v2;
    // Vector from point 1 to point 2
    v1 = Vector2(x2_ - x1_, y2_ - y1_);
    // Vector from point 1 to the circle's center
    v2 = Vector2(x3_ - x1_, y3_ - y1_);

    float dot = v1.x * v2.x + v1.y * v2.y;
    Vector2 proj1 = Vector2(((dot / (Vector2::length(v1))) * v1.x), ((dot / (Vector2::length(v1))) * v1.y));

    Vector2 midpt = Vector2(x1_ + proj1.x, y1_ + proj1.y);
    float distToCenter = (midpt.x - x3_) * (midpt.x - x3_) + (midpt.y - y3_) * (midpt.y - y3_);
    if (distToCenter > r3_ * r3_) return result;
    if (distToCenter == r3_ * r3_)
    {
        result.InsertSolution(midpt);
        return result;
    }
    float distToIntersection;
    if (distToCenter == 0)
    {
        distToIntersection = r3_;
    }
    else
    {
        distToCenter = sqrt(distToCenter);
        distToIntersection = sqrt(r3_ * r3_ - distToCenter * distToCenter);
    }
    float lineSegmentLength = 1 / Vector2::length(v1);
    v1 *= lineSegmentLength;
    v1 *= distToIntersection;

    Vector2 solution1 = midpt + v1;
    if ((solution1.x - x1_) * v1.x + (solution1.y - y1_) * v1.y > 0)
    {
        result.InsertSolution(solution1);
    }
    Vector2 solution2 = midpt - v1;
    if ((solution2.x - x1_) * v1.x + (solution2.y - y1_) * v1.y > 0)
    {
        result.InsertSolution(solution2);
    }
    return result;
}

// Circle to Ray
IntersectionObject IntersectionFunctions::CircleToRayIntersection(float x1_, float y1_, float r1_, float x2_, float y2_, float x3_, float y3_)
{
    return RayToCircleIntersection(x2_, y2_, x3_, y3_, x1_, y1_, r1_);
}

// Line to Line
IntersectionObject IntersectionFunctions::LineToLineIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_)
{
    IntersectionObject result;
    float r, s, d;
    // Make sure the lines aren't parallel
    if ((y2_ - y1_) / (x2_ - x1_) != (y4_ - y3_) / (x4_ - x3_))
    {
        d = (((x2_ - x1_) * (y4_ - y3_)) - (y2_ - y1_) * (x4_ - x3_));
        if (d != 0)
        {
            r = (((y1_ - y3_) * (x4_ - x3_)) - (x1_ - x3_) * (y4_ - y3_)) / d;
            s = (((y1_ - y3_) * (x2_ - x1_)) - (x1_ - x3_) * (y2_ - y1_)) / d;

            result.InsertSolution(x1_ + r * (x2_ - x1_), y1_ + r * (y2_ - y1_));
        }
    }
    return result;
}

// LineSegment to LineSegment
IntersectionObject IntersectionFunctions::LineSegmentToLineSegmentIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_)
{
    IntersectionObject result;
    float r, s, d;
    //Make sure the lines aren't parallel
    if ((y2_ - y1_) / (x2_ - x1_) != (y4_ - y3_) / (x4_ - x3_))
    {
        d = (((x2_ - x1_) * (y4_ - y3_)) - (y2_ - y1_) * (x4_ - x3_));
        if (d != 0)
        {
            r = (((y1_ - y3_) * (x4_ - x3_)) - (x1_ - x3_) * (y4_ - y3_)) / d;
            s = (((y1_ - y3_) * (x2_ - x1_)) - (x1_ - x3_) * (y2_ - y1_)) / d;
            if (r >= 0 && r <= 1)
            {
                if (s >= 0 && s <= 1)
                {
                    result.InsertSolution(x1_ + r * (x2_ - x1_), y1_ + r * (y2_ - y1_));
                }
            }
        }
    }
    return result;
}

// LineSegment to Line
IntersectionObject IntersectionFunctions::LineSegmentToLineIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_)
{
    IntersectionObject result;
    float r, s, d;
    // Make sure the lines aren't parallel
    if ((y2_ - y1_) / (x2_ - x1_) != (y4_ - y3_) / (x4_ - x3_))
    {
        d = (((x2_ - x1_) * (y4_ - y3_)) - (y2_ - y1_) * (x4_ - x3_));
        if (d != 0)
        {
            r = (((y1_ - y3_) * (x4_ - x3_)) - (x1_ - x3_) * (y4_ - y3_)) / d;
            s = (((y1_ - y3_) * (x2_ - x1_)) - (x1_ - x3_) * (y2_ - y1_)) / d;
            if (r >= 0 && r <= 1)
            {
                result.InsertSolution(x1_ + r * (x2_ - x1_), y1_ + r * (y2_ - y1_));
            }
        }
    }
    return result;
}

// Line to LineSement
IntersectionObject IntersectionFunctions::LineToLineSegmentIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_)
{
    return LineSegmentToLineIntersection(x3_, y3_, x4_, y4_, x1_, y1_, x2_, y2_);
}

// Ray to LineSegment
IntersectionObject IntersectionFunctions::RayToLineSegmentIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_)
{
    IntersectionObject result;
    float r, s, d;
    // Make sure the lines aren't parallel
    if ((y2_ - y1_) / (x2_ - x1_) != (y4_ - y3_) / (x4_ - x3_))
    {
        d = (((x2_ - x1_) * (y4_ - y3_)) - (y2_ - y1_) * (x4_ - x3_));
        if (d != 0)
        {
            r = (((y1_ - y3_) * (x4_ - x3_)) - (x1_ - x3_) * (y4_ - y3_)) / d;
            s = (((y1_ - y3_) * (x2_ - x1_)) - (x1_ - x3_) * (y2_ - y1_)) / d;
            if (r >= 0)
            {
                if (s >= 0 && s <= 1)
                {
                    result.InsertSolution(x1_ + r * (x2_ - x1_), y1_ + r * (y2_ - y1_));
                }
            }
        }
    }
    return result;
}

// LineSegment to Ray
IntersectionObject IntersectionFunctions::LineSegmentToRayIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_)
{
    return RayToLineSegmentIntersection(x3_, y3_, x4_, y4_, x1_, y1_, x2_, y2_);
}

// Ray to Line
IntersectionObject IntersectionFunctions::RayToLineIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_)
{
    IntersectionObject result;
    float r, s, d;
    // Make sure the lines aren't parallel
    if ((y2_ - y1_) / (x2_ - x1_) != (y4_ - y3_) / (x4_ - x3_))
    {
        d = (((x2_ - x1_) * (y4_ - y3_)) - (y2_ - y1_) * (x4_ - x3_));
        if (d != 0)
        {
            r = (((y1_ - y3_) * (x4_ - x3_)) - (x1_ - x3_) * (y4_ - y3_)) / d;
            s = (((y1_ - y3_) * (x2_ - x1_)) - (x1_ - x3_) * (y2_ - y1_)) / d;
            if (r >= 0)
            {
                result.InsertSolution(x1_ + r * (x2_ - x1_), y1_ + r * (y2_ - y1_));
            }
        }
    }
    return result;
}

// Line to Ray
IntersectionObject IntersectionFunctions::LineToRayIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_)
{
    return RayToLineIntersection(x3_, y3_, x4_, y4_, x1_, y1_, x2_, y2_);
}

// Ray to Ray
IntersectionObject IntersectionFunctions::RayToRayIntersection(float x1_, float y1_, float x2_, float y2_, float x3_, float y3_, float x4_, float y4_)
{
    IntersectionObject result;
    float r, s, d;
    // Make sure the lines aren't parallel
    if ((y2_ - y1_) / (x2_ - x1_) != (y4_ - y3_) / (x4_ - x3_))
    {
        d = (((x2_ - x1_) * (y4_ - y3_)) - (y2_ - y1_) * (x4_ - x3_));
        if (d != 0)
        {
            r = (((y1_ - y3_) * (x4_ - x3_)) - (x1_ - x3_) * (y4_ - y3_)) / d;
            s = (((y1_ - y3_) * (x2_ - x1_)) - (x1_ - x3_) * (y2_ - y1_)) / d;
            if (r >= 0)
            {
                if (s >= 0)
                {
                    result.InsertSolution(x1_ + r * (x2_ - x1_), y1_ + r * (y2_ - y1_));
                }
            }
        }
    }
    return result;
}

