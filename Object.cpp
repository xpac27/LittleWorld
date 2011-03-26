#include "Object.h"

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

