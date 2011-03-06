#include "Object.h"

Object::Object(World *w, float h) : world(w), height(h)
{
    x    = 0.f;
    y    = 0.f;
    size = 32.f;
}

void Object::init()
{
    alfSize     = size / 2.f;
    quarterSize = size / 4.f;
    index       = height > 0.f ? 2.f : 1.f;
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
        glColor4f(0.2f, 0.2f, 0.2f, 1.f);

        // FACE LEFT
        glBegin(GL_QUADS);

            glVertex2f(-alfSize, 0.f);
            glVertex2f(-alfSize, -height);
            glVertex2f(0.f, -height + quarterSize);
            glVertex2f(0.f, quarterSize);
            glVertex2f(-alfSize, 0.f);

        glEnd();

        glColor4f(0.6f, 0.6f, 0.6f, 1.f);

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

        glVertex2f(0.f, -quarterSize);
        glVertex2f(alfSize, 0.f);

        glVertex2f(alfSize, 0.f);
        glVertex2f(0.f, quarterSize);

        glVertex2f(0.f, quarterSize);
        glVertex2f(-alfSize, 0.f);

        glVertex2f(-alfSize, 0.f);
        glVertex2f(0.f, -quarterSize);

    glEnd();

    if (height != 0)
    {
        glPopMatrix();
    }
}

float Object::getX()
{
    return x;
}

float Object::getY()
{
    return y;
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

