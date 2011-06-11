#include "Object.h"

using namespace std;

Object::Object(World *W, float h, bool s) : world(W), height(h), shadow(s)
{
    index = height > 0.f ? 2.f : 1.f;

    setSize(32.f);
}

void Object::init()
{
}

void Object::setSize(float s)
{
    size = s;

    float alfSize = size / 2.f;
    float quarterSize = size / 4.f;
    float heighthSize = size / 8.f;

    if (height > 0.f)
    {
        faceL.clear();
        faceL.addPoint(-alfSize, 0.f);
        faceL.addPoint(-alfSize, -height);
        faceL.addPoint(0.f, -height + quarterSize);
        faceL.addPoint(0.f, quarterSize);

        faceR.clear();
        faceR.addPoint(alfSize, 0.f);
        faceR.addPoint(alfSize, -height);
        faceR.addPoint(0.f, -height + quarterSize);
        faceR.addPoint(0.f, quarterSize);
    }

    faceT.clear();
    faceT.addPoint(0.f, -quarterSize);
    faceT.addPoint(alfSize, 0.f);
    faceT.addPoint(0.f, quarterSize);
    faceT.addPoint(-alfSize, 0.f);
}

void Object::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

void Object::draw()
{
    // TODO remove
    glBegin(GL_LINES);
    glColor3d(size / 2.f, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(size / 2.f, 0.0, 0.0);
    glColor3d(0.0, size / 2.f, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, size / 2.f, 0.0);
    glColor3d(0.0, 0.0, size / 2.f);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, size / 2.f);
    glEnd();
    return;

    if (height == 0)
    {
        glNormal3f(0.f, -1.f, 0.f);
        faceT.draw();
    }
    else
    {
        glNormal3f(0.f, -1.f, 0.f);
        faceT.draw();

        glColor4f(0.6f, 0.6f, 0.6f, 1.f);

        glNormal3f(-0.7f, 0.7f, 0.f);
        faceL.draw();

        glNormal3f(0.7f, 0.7f, 0.f);
        faceR.draw();
    }
}

void Object::outline()
{
    glColor4f(1.f, 1.f, 1.f, 0.04);

    if (height == 0)
    {
        faceT.outline();
    }
    else
    {
        faceL.outline();
        faceR.outline();
        faceT.outline();
    }
}

void Object::updateShadows(Light *l)
{
    if (shadow && height > 0.f)
    {
        if (l->getIntensityAtPosition(position) > 0.01f)
        {
        }
    }
}

void Object::drawShadow()
{
}

float Object::getX()
{
    return position.x;
}

float Object::getY()
{
    return position.y;
}

float Object::getHeight()
{
    return height;
}

float Object::getSize()
{
    return size;
}

bool Object::shadowEnabled()
{
    return shadow;
}

