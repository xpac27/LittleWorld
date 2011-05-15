#include "Quad.h"

using namespace std;

Quad::Quad()
{
    set(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
}

Quad::Quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    set(x1, y1, x2, y2, x3, y3, x4, y4);
}

void Quad::set(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    p3.x = x3;
    p3.y = y3;
    p4.x = x4;
    p4.y = y4;

    s1.set(x1, y1, x2, y2);
    s2.set(x2, y2, x3, y3);
    s3.set(x3, y3, x4, y4);
    s4.set(x4, y4, x1, y1);
}

void Quad::translate(float tx, float ty)
{
    p1.x += tx;
    p1.y += ty;
    p2.x += tx;
    p2.y += ty;
    p3.x += tx;
    p3.y += ty;
    p4.x += tx;
    p4.y += ty;

    s1.translate(tx, ty);
    s2.translate(tx, ty);
    s3.translate(tx, ty);
    s4.translate(tx, ty);
}

void Quad::draw()
{
    glBegin(GL_QUADS);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p3.x, p3.y);
        glVertex2f(p4.x, p4.y);
    glEnd();
}

void Quad::outline()
{
    glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p3.x, p3.y);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(p3.x, p3.y);
        glVertex2f(p4.x, p4.y);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(p4.x, p4.y);
        glVertex2f(p1.x, p1.y);
    glEnd();
}

bool Quad::containsSegment(Segment *s)
{
    return containsPosition(&s->p1) && containsPosition(&s->p2);
}

bool Quad::containsPosition(Vector2 *p)
{
    return ContainFunctions::PointInQuad(p->x, p->y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
}

