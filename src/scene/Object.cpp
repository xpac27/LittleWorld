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

    if (height > 0.f)
    {
        faceL.clear();
        faceL.addPoint(-alfSize, 0.f,    alfSize);
        faceL.addPoint(-alfSize, height, alfSize);
        faceL.addPoint( alfSize, height, alfSize);
        faceL.addPoint( alfSize, 0.f,    alfSize);

        faceR.clear();
        faceR.addPoint(alfSize, 0.f,    alfSize );
        faceR.addPoint(alfSize, height, alfSize );
        faceR.addPoint(alfSize, height,-alfSize );
        faceR.addPoint(alfSize, 0.f,   -alfSize );
    }

    faceT.clear();
    faceT.addPoint(-alfSize, height, -alfSize);
    faceT.addPoint( alfSize, height, -alfSize);
    faceT.addPoint( alfSize, height,  alfSize);
    faceT.addPoint(-alfSize, height,  alfSize);
}

void Object::setPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void Object::draw()
{
    if (height == 0)
    {
        glNormal3f(0.f, -1.f, 0.f);
        faceT.draw();
    }
    else
    {
        glNormal3f(0.f, 1.f, 0.f);
        faceT.draw();

        glColor4f(0.6f, 0.6f, 0.6f, 1.f);

        glNormal3f(0.f, 0.f, 1.f);
        faceL.draw();

        glNormal3f(1.f, 0.f, 0.f);
        faceR.draw();
    }
}

void Object::drawOutline()
{
    glColor4f(1.f, 1.f, 1.f, 0.04);

    if (height == 0)
    {
        faceT.drawOutline();
    }
    else
    {
        faceL.drawOutline();
        faceR.drawOutline();
        faceT.drawOutline();
    }
}

void Object::updateShadows(Light *l)
{
    if (shadow && height > 0.f)
    {
        //if (l->getIntensityAtPosition(position) > 0.01f)
        //{
        //}
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

float Object::getZ()
{
    return position.z;
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

