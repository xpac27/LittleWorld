#include "Triangle.h"

using namespace std;

Triangle::Triangle(Point *p1, Point *p2, Point *p3)
{
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;

    cw = true;
    lighted = false;
    transformed = false;

    update();
}

void Triangle::update()
{
    normalCW = Vector3Util::Cross(*points[1] - *points[0], *points[2] - *points[0]);
    Vector3Util::Normalize(normalCW);
    normalCCW = normalCW * -1;
    resetTransformation();
}

void Triangle::setTransformationMIN(Vector3 v)
{
    pointsTransformed[0] = pointsTransformed[0] - v;
    pointsTransformed[1] = pointsTransformed[1] - v;
    pointsTransformed[2] = pointsTransformed[2] - v;
    transformed = true;
}

void Triangle::setTransformationADD(Vector3 v)
{
    pointsTransformed[0] = pointsTransformed[0] + v;
    pointsTransformed[1] = pointsTransformed[1] + v;
    pointsTransformed[2] = pointsTransformed[2] + v;
    transformed = true;
}

void Triangle::setTransformationMUL(float n)
{
    pointsTransformed[0] = pointsTransformed[0] * n;
    pointsTransformed[1] = pointsTransformed[1] * n;
    pointsTransformed[2] = pointsTransformed[2] * n;
    transformed = true;
}

void Triangle::setTransformationDIV(float n)
{
    pointsTransformed[0] = pointsTransformed[0] / n;
    pointsTransformed[1] = pointsTransformed[1] / n;
    pointsTransformed[2] = pointsTransformed[2] / n;
    transformed = true;
}

void Triangle::resetTransformation()
{
    pointsTransformed[0] = (*points[0]);
    pointsTransformed[1] = (*points[1]);
    pointsTransformed[2] = (*points[2]);
    transformed = false;
}

void Triangle::setCW()
{
    cw = true;
}

void Triangle::setCCW()
{
    cw = false;
}

void Triangle::setNormal()
{
    if (cw)
    {
        glNormal3f(normalCW.x, normalCW.y, normalCW.z);
    }
    else
    {
        glNormal3f(normalCCW.x, normalCCW.y, normalCCW.z);
    }
}

void Triangle::setAllVertex()
{
    if (cw)
    {
        if (transformed)
        {
            glVertex3f(pointsTransformed[0].x, pointsTransformed[0].y, pointsTransformed[0].z);
            glVertex3f(pointsTransformed[1].x, pointsTransformed[1].y, pointsTransformed[1].z);
            glVertex3f(pointsTransformed[2].x, pointsTransformed[2].y, pointsTransformed[2].z);
        }
        else
        {
            glVertex3f(points[0]->x, points[0]->y, points[0]->z);
            glVertex3f(points[1]->x, points[1]->y, points[1]->z);
            glVertex3f(points[2]->x, points[2]->y, points[2]->z);
        }
    }
    else
    {
        if (transformed)
        {
            glVertex3f(pointsTransformed[2].x, pointsTransformed[2].y, pointsTransformed[2].z);
            glVertex3f(pointsTransformed[1].x, pointsTransformed[1].y, pointsTransformed[1].z);
            glVertex3f(pointsTransformed[0].x, pointsTransformed[0].y, pointsTransformed[0].z);
        }
        else
        {
            glVertex3f(points[2]->x, points[2]->y, points[2]->z);
            glVertex3f(points[1]->x, points[1]->y, points[1]->z);
            glVertex3f(points[0]->x, points[0]->y, points[0]->z);
        }
    }
}

Vector3 Triangle::getNormal()
{
    return cw ? normalCW : normalCCW;
}

