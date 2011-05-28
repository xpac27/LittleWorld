#include "Segment.h"

using namespace std;

Segment::Segment(Vector2 p1, Vector2 p2)
{
    points.clear();
    points.push_back(p1);
    points.push_back(p2);
}

Segment::Segment(float x1, float y1, float x2, float y2)
{
    Segment(Vector2(x1, y1), Vector2(x2, y2));
}

void Segment::translate(Vector2 t)
{
    for (unsigned int i = 0; i < points.size(); i ++)
    {
        points[i] += t;
    }
}

void Segment::draw()
{
    glBegin(GL_LINES);
    for (unsigned int i = 0; i < points.size(); i ++)
    {
        glVertex2f(points[i].x, points[i].y);
    }
    glEnd();
}

void Segment::collectIntesectionToSegment(Segment *s, std::vector<Vector2> *pointList)
{
    IntersectionObject result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(points[0].x, points[0].y, points[1].x, points[1].y, s->getPoint(0)->x, s->getPoint(0)->y, s->getPoint(1)->x, s->getPoint(1)->y);
    if (result.points.size() == 1)
    {
        pointList->push_back(result.points[0]);
    }
}

Vector2 *Segment::getPoint(unsigned int i)
{
    return &points[i];
}

vector<Vector2> *Segment::getPoints()
{
    return &points;
}

