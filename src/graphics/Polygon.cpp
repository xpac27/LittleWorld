#include "Polygon.h"

using namespace std;

Polygon::Polygon()
{
}

void Polygon::addPoint(Vector3 p)
{
    points.push_back(p);
}

void Polygon::addPoint(float x, float y, float z)
{
    addPoint(Vector3(x, y, z));
}

void Polygon::clear()
{
    points.clear();
}

void Polygon::translate(Vector3 t)
{
    for (unsigned int i = 0; i < points.size(); i ++)
    {
        points[i] += t;
    }
}

void Polygon::draw()
{
    glBegin(GL_POLYGON);
    drawVertices();
    glEnd();
}

void Polygon::drawOutline()
{
    glBegin(GL_LINE_LOOP);
    drawVertices();
    glEnd();
}

void Polygon::drawVertices()
{
    for (unsigned int i = 0; i < points.size(); i ++)
    {
        glVertex3f(points[i].x, points[i].y, points[i].z);
    }
}

int Polygon::getTotalPoint()
{
    return points.size();
}

vector<Vector3> *Polygon::getPoints()
{
    return &points;
}

Vector3 *Polygon::getPoint(unsigned int i)
{
    return &points[i];
}

