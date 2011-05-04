#include "Object.h"

using namespace std;

Object::Object(World *w, float h) : world(w), height(h)
{
    index = height > 0.f ? 2.f : 1.f;

    position.set(0.f, 0.f, 0.f);
    setSize(32.f);
}

void Object::init()
{
}

Object Object::operator<(Object &o)
{
    return height < 2.f ? o : *this;
}

void Object::setSize(float s)
{
    size        = s;
    alfSize     = size / 2.f;
    quarterSize = size / 4.f;
}

void Object::setPosition(float x, float y)
{
    position.set(x, y);
}

void Object::draw()
{
    if (height != 0)
    {
        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
    }

    // FACE TOP
    glBegin(GL_QUADS);
        glVertex2f(0.f, -quarterSize);
        glVertex2f(alfSize, 0.f);
        glVertex2f(0.f, quarterSize);
        glVertex2f(-alfSize, 0.f);
    glEnd();

    if (height != 0)
    {
        glPopMatrix();
    }

    if (height != 0)
    {
        glColor4f(0.6f, 0.6f, 0.6f, 1.f);

        // FACE LEFT
        glBegin(GL_QUADS);
            glVertex2f(-alfSize, 0.f);
            glVertex2f(-alfSize, -height);
            glVertex2f(0.f, -height + quarterSize);
            glVertex2f(0.f, quarterSize);
        glEnd();

        // FACE RIGHT
        glBegin(GL_QUADS);
            glVertex2f(alfSize, 0.f);
            glVertex2f(alfSize, -height);
            glVertex2f(0.f, -height + quarterSize);
            glVertex2f(0.f, quarterSize);
        glEnd();
    }
}

void Object::drawOutline()
{
    glColor4f(1.f, 1.f, 1.f, 0.6f);

    if (height != 0)
    {
        // OUTLINE FACE LEFT
        glBegin(GL_LINES);
            glVertex2f(-alfSize, 0.f);
            glVertex2f(-alfSize, -height);
            glVertex2f(0.f, -height + quarterSize);
            glVertex2f(0.f, quarterSize);
        glEnd();

        // OUTLINE FACE RIGHT
        glBegin(GL_LINES);
            glVertex2f(alfSize, 0.f);
            glVertex2f(alfSize, -height);
            glVertex2f(0.f, -height + quarterSize);
            glVertex2f(0.f, quarterSize);
        glEnd();

        // OUTLINE FACE BOTTOM
        glBegin(GL_LINES);
            glVertex2f(0.f, quarterSize);
            glVertex2f(alfSize, 0.f);
            glVertex2f(0.f, quarterSize);
            glVertex2f(-alfSize, 0.f);
        glEnd();
    }

    if (height != 0)
    {
        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
    }

    // OUTLINE FACE TOP
    glBegin(GL_LINES);
        glVertex2f(alfSize, 0.f);
        glVertex2f(0.f, quarterSize);
        glVertex2f(0.f, quarterSize);
        glVertex2f(-alfSize, 0.f);
        glVertex2f(-alfSize, 0.f);
        glVertex2f(0.f, -quarterSize);
        glVertex2f(0.f, -quarterSize);
        glVertex2f(alfSize, 0.f);
    glEnd();

    if (height != 0)
    {
        glPopMatrix();
    }
}

void Object::drawShadow(float lx, float ly, list<Object*> objects)
{
    if (height != 0)
    {
        float edgeBR[4] = {alfSize, 0.f, 0.f, quarterSize};
        float edgeBL[4] = {0.f, quarterSize, -alfSize, 0.f};
        float edgeTR[4] = {0.f, -quarterSize, alfSize, 0.f};
        float edgeTL[4] = {-alfSize, 0.f, 0.f, -quarterSize};

        drawEdgeShadow(edgeBR, lx, ly);
        drawEdgeShadow(edgeBL, lx, ly);
        drawEdgeShadow(edgeTR, lx, ly);
        drawEdgeShadow(edgeTL, lx, ly);

        // TODO:
        // - loop through all objects as o
        // - if o has an height
        // - if base segment is within the shadow volume
        //    - fill it with shadow
        // - else
        //    - erase shadow
        //    - if base segment is intersecting shadow segements
        //        - draw the shadow on it

        // ERASE SHADOW:
        //glStencilFunc(GL_EQUAL, 1, 1);
        //glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);
    }
}

void Object::drawEdgeShadow(float edge[4], float lx, float ly)
{
    if (doesEdgeCastShadow(edge[0], edge[1], edge[2], edge[3], lx, ly))
    {
        glBegin(GL_QUADS);
            glVertex2f(edge[0], edge[1]);
            glVertex2f(edge[0] + ((edge[0] - lx) * (height / 64.f)), edge[1] + ((edge[1] - ly) * (height / 64.f)));
            glVertex2f(edge[2] + ((edge[2] - lx) * (height / 64.f)), edge[3] + ((edge[3] - ly) * (height / 64.f)));
            glVertex2f(edge[2], edge[3]);
        glEnd();
    }
}

bool Object::doesEdgeCastShadow(float px1, float py1, float px2, float py2, float lx, float ly)
{
    // normal of 2nd point minus 1st point
    float nx = -1 * (py2 - py1);
    float ny = px2 - px1;

    // light minus 1st point
    lx = px1 - lx;
    ly = py1 - ly;

    if (dotProduct(nx, ny, lx, ly) < 0.f)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float Object::dotProduct(float x1, float y1, float x2, float y2)
{
    return x1 * x2 + y1 * y2;
}

float Object::getX()
{
    return position.x;
}

float Object::getY()
{
    return position.y;
}

float Object::getIndex()
{
    return index;
}

float Object::getHeight()
{
    return height;
}

float Object::getSize()
{
    return size;
}

