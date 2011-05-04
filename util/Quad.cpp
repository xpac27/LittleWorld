#include "Quad.h"

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
    p1.set(x1, y1);
    p2.set(x2, y2);
    p3.set(x3, y3);
    p4.set(x4, y4);
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

