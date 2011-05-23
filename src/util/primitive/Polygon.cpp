#include "Polygon.h"

using namespace std;

Polygon::Polygon()
{
}

void Polygon::addPoint(Vector2 p)
{
    points.push_back(p);
    computeSegments();
}

void Polygon::addPoint(float x, float y)
{
    addPoint(Vector2(x, y));
}

void Polygon::computeSegments()
{
    segments.clear();
    if (points.size() > 0)
    {
        for (unsigned int i = 1; i < points.size(); i ++)
        {
            segments.push_back(Segment(points[i - 1], points[i]));
        }
        segments.push_back(Segment(points[points.size() - 1], points[0]));
    }
}

void Polygon::clear()
{
    points.clear();
    segments.clear();
}

void Polygon::translate(Vector2 t)
{
    for (unsigned int i = 0; i < points.size(); i ++)
    {
        points[i] += t;
    }
    for (unsigned int i = 0; i < segments.size(); i ++)
    {
        segments[i].translate(t);
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

bool Polygon::containsSegment(Segment *s)
{
    return containsPosition(&s->p1) && containsPosition(&s->p2);
}

bool Polygon::containsPosition(Vector2 *p)
{
    return ContainFunctions::PointInPolygon(p, &points);
}

int Polygon::getTotalPoint()
{
    return points.size();
}

int Polygon::getTotalSegment()
{
    return segments.size();
}

vector<Vector2> *Polygon::getPoinst()
{
    return &points;
}

vector<Segment> *Polygon::getSegments()
{
    return &segments;
}

Vector2 *Polygon::getPoint(unsigned int i)
{
    return &points[i];
}

Segment *Polygon::getSegment(unsigned int i)
{
    return &segments[i];
}

