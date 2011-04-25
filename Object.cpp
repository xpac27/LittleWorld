#include "Object.h"

using namespace std;

Object::Object(World *w, float h) : world(w), height(h)
{
    index = height > 0.f ? 2.f : 1.f;
    touched = false;

    position.set(0.f, 0.f, 0.f);
    setSize(32.f);
}

void Object::init()
{
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
        glColor4f(0.5f, 0.5f, 0.5f, 1.f);
        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
    }

    if (touched)
    {
        touched = false;
        glColor4f(0.2f, 0.8f, 0.2f, 1.f);
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

        //glColor4f(0.2f, 0.2f, 0.2f, 1.f);

        // FACE LEFT
        glBegin(GL_QUADS);

            glVertex2f(-alfSize, 0.f);
            glVertex2f(-alfSize, -height);
            glVertex2f(0.f, -height + quarterSize);
            glVertex2f(0.f, quarterSize);
            glVertex2f(-alfSize, 0.f);

        glEnd();

        //glColor4f(0.6f, 0.6f, 0.6f, 1.f);

        // FACE RIGHT
        glBegin(GL_QUADS);

            glVertex2f(alfSize, 0.f);
            glVertex2f(alfSize, -height);
            glVertex2f(0.f, -height + quarterSize);
            glVertex2f(0.f, quarterSize);
            glVertex2f(alfSize, 0.f);

        glEnd();
    }

    glColor4f(1.f, 1.f, 1.f, 0.5f);

    if (height != 0)
    {
        // OUTLINE FACE LEFT
        glBegin(GL_LINES);

            glVertex2f(-alfSize, 0.f);
            glVertex2f(-alfSize, -height);

            glVertex2f(-alfSize, -height);
            glVertex2f(0.f, -height + quarterSize);

            glVertex2f(0.f, -height + quarterSize);
            glVertex2f(0.f, quarterSize);

            glVertex2f(-alfSize, 0.f);
            glVertex2f(-alfSize, 0.f);

        glEnd();

        // OUTLINE FACE RIGHT
        glBegin(GL_LINES);

            glVertex2f(alfSize, 0.f);
            glVertex2f(alfSize, -height);

            glVertex2f(alfSize, -height);
            glVertex2f(0.f, -height + quarterSize);

            glVertex2f(0.f, -height + quarterSize);
            glVertex2f(0.f, quarterSize);

            glVertex2f(alfSize, 0.f);
            glVertex2f(alfSize, 0.f);

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

        glVertex2f(0.f, -quarterSize);
        glVertex2f(alfSize, 0.f);

        glVertex2f(-alfSize, 0.f);
        glVertex2f(0.f, -quarterSize);

    glEnd();

    if (height != 0)
    {
        glPopMatrix();
    }
}

void Object::drawShadowExclusions(float lightX, float lightY)
{
    if (height != 0)
    {
        glPushMatrix();
        glTranslatef(0.f, -height, 0.f);
    }

    glBegin(GL_QUADS);

        glVertex2f(0.f, -quarterSize);
        glVertex2f(alfSize, 0.f);
        glVertex2f(0.f, quarterSize);
        glVertex2f(-alfSize, 0.f);

    glEnd();

    if (height != 0)
    {
        glPopMatrix();

        float p0x, p0y, p1x, p1y, h;

        h = height / 64.f;

        p0x = alfSize;
        p0y = 0.f;
        p1x = 0.f;
        p1y = quarterSize;

        if (!doesEdgeCastShadow(p0x, p0y, p1x, p1y, lightX, lightY))
        {
            glBegin(GL_QUADS);
                glVertex2f(p1x, p1y);
                glVertex2f(p1x, -height);
                glVertex2f(p0x, -height + p0y);
                glVertex2f(p0x, p0y);
                glVertex2f(p1x, p1y);
            glEnd();
        }

        p0x = 0.f;
        p0y = quarterSize;
        p1x = -alfSize;
        p1y = 0.f;

        if (!doesEdgeCastShadow(p0x, p0y, p1x, p1y, lightX, lightY))
        {
            glBegin(GL_QUADS);
                glVertex2f(p1x, p1y);
                glVertex2f(p1x, -height);
                glVertex2f(p0x, -height + p0y);
                glVertex2f(p0x, p0y);
                glVertex2f(p1x, p1y);
            glEnd();
        }
    }
}

void Object::drawShadow(float lightX, float lightY)
{
    if (height != 0)
    {
        float p0x, p0y, p1x, p1y, h;

        h = height / 64.f;

        p0x = alfSize;
        p0y = 0.f;
        p1x = 0.f;
        p1y = quarterSize;

        if (doesEdgeCastShadow(p0x, p0y, p1x, p1y, lightX, lightY))
        {
            glBegin(GL_QUADS);
                glVertex2f(p0x, p0y);
                glVertex2f(p0x + ((p0x - lightX) * h), p0y + ((p0y - lightY) * h));
                glVertex2f(p1x + ((p1x - lightX) * h), p1y + ((p1y - lightY) * h));
                glVertex2f(p1x, p1y);
            glEnd();
            //glBegin(GL_QUADS);
                //glVertex2f(p0x, -height + p0y);
                //glVertex2f(p0x + ((p0x - lightX) * h), p0y + ((p0y - lightY) * h));
                //glVertex2f(p1x + ((p1x - lightX) * h), p1y + ((p1y - lightY) * h));
                //glVertex2f(p1x, -height + p1y);
            //glEnd();
        }

        p0x = 0.f;
        p0y = quarterSize;
        p1x = -alfSize;
        p1y = 0.f;

        if (doesEdgeCastShadow(p0x, p0y, p1x, p1y, lightX, lightY))
        {
            glBegin(GL_QUADS);
                glVertex2f(p0x, p0y);
                glVertex2f(p0x + ((p0x - lightX) * h), p0y + ((p0y - lightY) * h));
                glVertex2f(p1x + ((p1x - lightX) * h), p1y + ((p1y - lightY) * h));
                glVertex2f(p1x, p1y);
            glEnd();
            //glBegin(GL_QUADS);
                //glVertex2f(p0x, -height + p0y);
                //glVertex2f(p0x + ((p0x - lightX) * h), p0y + ((p0y - lightY) * h));
                //glVertex2f(p1x + ((p1x - lightX) * h), p1y + ((p1y - lightY) * h));
                //glVertex2f(p1x, -height + p1y);
            //glEnd();
        }

        p0x = 0.f;
        p0y = -quarterSize;
        p1x = alfSize;
        p1y = 0.f;

        if (doesEdgeCastShadow(p0x, p0y, p1x, p1y, lightX, lightY))
        {
            glBegin(GL_QUADS);
                glVertex2f(p0x, p0y);
                glVertex2f(p0x + ((p0x - lightX) * h), p0y + ((p0y - lightY) * h));
                glVertex2f(p1x + ((p1x - lightX) * h), p1y + ((p1y - lightY) * h));
                glVertex2f(p1x, p1y);
            glEnd();
            //glBegin(GL_QUADS);
                //glVertex2f(p0x, -height + p0y);
                //glVertex2f(p0x + ((p0x - lightX) * h), p0y + ((p0y - lightY) * h));
                //glVertex2f(p1x + ((p1x - lightX) * h), p1y + ((p1y - lightY) * h));
                //glVertex2f(p1x, -height + p1y);
            //glEnd();
        }

        p0x = -alfSize;
        p0y = 0.f;
        p1x = 0.f;
        p1y = -quarterSize;

        if (doesEdgeCastShadow(p0x, p0y, p1x, p1y, lightX, lightY))
        {
            glBegin(GL_QUADS);
                glVertex2f(p0x, p0y);
                glVertex2f(p0x + ((p0x - lightX) * h), p0y + ((p0y - lightY) * h));
                glVertex2f(p1x + ((p1x - lightX) * h), p1y + ((p1y - lightY) * h));
                glVertex2f(p1x, p1y);
            glEnd();
            //glBegin(GL_QUADS);
                //glVertex2f(p0x, -height + p0y);
                //glVertex2f(p0x + ((p0x - lightX) * h), p0y + ((p0y - lightY) * h));
                //glVertex2f(p1x + ((p1x - lightX) * h), p1y + ((p1y - lightY) * h));
                //glVertex2f(p1x, -height + p1y);
            //glEnd();
        }
    }
}

void Object::drawShadowSides(float lightX, float lightY)
{
    if (height != 0)
    {
        float p0x, p0y, p1x, p1y, h;

        h = height / 64.f;

        p0x = alfSize;
        p0y = 0.f;
        p1x = 0.f;
        p1y = quarterSize;

        if (doesEdgeCastShadow(p0x, p0y, p1x, p1y, lightX, lightY))
        {
            glBegin(GL_QUADS);
                glVertex2f(p0x, p0y);
                glVertex2f(p0x, -height);
                glVertex2f(p1x, -height + p1y);
                glVertex2f(p1x, p1y);
                glVertex2f(p0x, p0y);
            glEnd();
        }

        p0x = 0.f;
        p0y = quarterSize;
        p1x = -alfSize;
        p1y = 0.f;

        if (doesEdgeCastShadow(p0x, p0y, p1x, p1y, lightX, lightY))
        {
            glBegin(GL_QUADS);
                glVertex2f(p1x, p1y);
                glVertex2f(p1x, -height);
                glVertex2f(p0x, -height + p0y);
                glVertex2f(p0x, p0y);
                glVertex2f(p1x, p1y);
            glEnd();
        }
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

