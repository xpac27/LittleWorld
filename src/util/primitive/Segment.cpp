#include "Segment.h"

Segment::Segment()
{
    set(0.f, 0.f, 0.f, 0.f);
}

Segment::Segment(float x1, float y1, float x2, float y2)
{
    set(x1, y1, x2, y2);
}

Segment::Segment(Vector2 p1, Vector2 p2)
{
    set(p1.x, p1.y, p2.x, p2.y);
}

void Segment::set(float x1, float y1, float x2, float y2)
{
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
}

void Segment::translate(Vector2 t)
{
    p1 += t;
    p2 += t;
}

void Segment::draw()
{
    glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    glEnd();
}

void Segment::collectIntesectionToSegment(Segment *s, std::vector<Vector2> *pointList)
{
    IntersectionObject result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(p1.x, p1.y, p2.x, p2.y, s->p1.x, s->p1.y, s->p2.x, s->p2.y);
    if (result.NumberOfSolutions() == 1)
    {
        pointList->push_back(result.points[0]);
    }
}

