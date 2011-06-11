#include "Polygon.h"

using namespace std;

Polygon::Polygon()
{
}

void Polygon::addPoint(Vector2 p)
{
    points.push_back(p);
}

void Polygon::addPoint(float x, float y)
{
    addPoint(Vector2(x, y));
}

void Polygon::clear()
{
    points.clear();
}

void Polygon::translate(Vector2 t)
{
    for (unsigned int i = 0; i < points.size(); i ++)
    {
        points[i] += t;
    }
}

void Polygon::draw()
{
    glBegin(GL_POLYGON);
    for (unsigned int i = 0; i < points.size(); i ++)
    {
        glVertex2f(points[i].x, points[i].y);
    }
    glEnd();
}

void Polygon::outline()
{
    glBegin(GL_LINE_LOOP);
    for (unsigned int i = 0; i < points.size(); i ++)
    {
        glVertex2f(points[i].x, points[i].y);
    }
    glEnd();
}

int Polygon::getTotalPoint()
{
    return points.size();
}

vector<Vector2> *Polygon::getPoints()
{
    return &points;
}

Vector2 *Polygon::getPoint(unsigned int i)
{
    return &points[i];
}

