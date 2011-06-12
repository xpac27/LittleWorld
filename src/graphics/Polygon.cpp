#include "Polygon.h"

using namespace std;

Polygon::Polygon()
{
}

void Polygon::addTriangle(Triangle t)
{
    triangles.push_back(t);
}

void Polygon::addTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
    addTriangle(Triangle(x1, y1, z1, x2, y2, z2, x3, y3, z3));
}

void Polygon::clear()
{
    triangles.clear();
}

void Polygon::translate(Vector3 t)
{
    for (unsigned int i = 0; i < triangles.size(); i ++)
    {
        triangles[i].translate(t);
    }
}

void Polygon::draw()
{
    for (unsigned int i = 0; i < triangles.size(); i ++)
    {
        triangles[i].draw();
    }
}

void Polygon::drawOutline()
{
    for (unsigned int i = 0; i < triangles.size(); i ++)
    {
        triangles[i].drawOutline();
    }
}

