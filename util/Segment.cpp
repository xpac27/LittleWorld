#include "Segment.h"

Segment::Segment()
{
    set(0.f, 0.f, 0.f, 0.f);
}

Segment::Segment(float x1, float y1, float x2, float y2)
{
    set(x1, y1, x2, y2);
}

void Segment::set(float x1, float y1, float x2, float y2)
{
    p1.set(x1, y1);
    p2.set(x2, y2);
}

void Segment::draw()
{
    glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    glEnd();
}

