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
    size = s;

    float alfSize = size / 2.f;
    float quarterSize = size / 4.f;

    faceLeft.set(-alfSize, 0.f, -alfSize, -height, 0.f, -height + quarterSize, 0.f, quarterSize);
    faceRight.set(alfSize, 0.f, alfSize, -height, 0.f, -height + quarterSize, 0.f, quarterSize);
    faceTop.set(0.f, -quarterSize, alfSize, 0.f, 0.f, quarterSize, -alfSize, 0.f);

    edgeBL.set(0.f, quarterSize, -alfSize, 0.f);
    edgeBR.set(alfSize, 0.f, 0.f, quarterSize);
    edgeTL.set(-alfSize, 0.f, 0.f, -quarterSize);
    edgeTR.set(0.f, -quarterSize, alfSize, 0.f);
}

void Object::setPosition(float x, float y)
{
    position.set(x, y);
}

void Object::draw()
{
    if (height == 0)
    {
        faceTop.draw();
    }
    else
    {
        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
        faceTop.draw();
        glPopMatrix();
        glColor4f(0.6f, 0.6f, 0.6f, 1.f);
        faceLeft.draw();
        faceRight.draw();
    }
}

void Object::drawOutline()
{
    glColor4f(1.f, 1.f, 1.f, 0.6f);

    if (height == 0)
    {
        faceTop.outline();
    }
    else
    {
        faceLeft.outline();
        faceRight.outline();
        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
        faceTop.outline();
        glPopMatrix();
    }
}

Quad Object::getEdgeShadow(Segment *edge, float lx, float ly)
{
    float h = height / 64.f;

    return Quad
    (
        edge->p1.x, edge->p1.y,
        edge->p1.x + (edge->p1.x - lx) * h, edge->p1.y + (edge->p1.y - ly) * h,
        edge->p2.x + (edge->p2.x - lx) * h, edge->p2.y + (edge->p2.y - ly) * h,
        edge->p2.x, edge->p2.y
    );
}

void Object::drawShadow(float lx, float ly, list<Object*> objects)
{
    if (height != 0)
    {
        Quad shadowBR = getEdgeShadow(&edgeBR, lx, ly);
        Quad shadowBL = getEdgeShadow(&edgeBL, lx, ly);
        Quad shadowTR = getEdgeShadow(&edgeTR, lx, ly);
        Quad shadowTL = getEdgeShadow(&edgeTL, lx, ly);

        if (doesEdgeCastShadow(&edgeBR, lx, ly))
        {
            shadowBR.draw();
        }
        if (doesEdgeCastShadow(&edgeBL, lx, ly))
        {
            shadowBL.draw();
        }
        if (doesEdgeCastShadow(&edgeTR, lx, ly))
        {
            shadowTR.draw();
        }
        if (doesEdgeCastShadow(&edgeTL, lx, ly))
        {
            shadowTL.draw();
        }

        // - loop through all objects as o
        //for (list<Object*>::iterator i = objects.begin(); i != objects.end(); ++ i)
        //{
            // - if o has an height
            //if ((*i)->getHeight() != 0)
            //{
                // - if base segment is within the shadow volume
                //if (pointWithin)
                //    - fill it with shadow
                // - else
                //    - erase shadow
                //    - if base segment is intersecting shadow segements
                //        - draw the shadow on it
            //}
        //}

        // ERASE SHADOW:
        //glStencilFunc(GL_EQUAL, 1, 1);
        //glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);
    }
}

bool Object::doesEdgeCastShadow(Segment *edge, float lx, float ly)
{
    // normal of 2nd point minus 1st point
    float nx = -1 * (edge->p2.y - edge->p1.y);
    float ny = edge->p2.x - edge->p1.x;

    // light minus 1st point
    lx = edge->p1.x - lx;
    ly = edge->p1.y - ly;

    // cross product
    if (nx * lx + ny * ly < 0.f)
    {
        return true;
    }
    else
    {
        return false;
    }
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

