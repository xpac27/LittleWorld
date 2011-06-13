#include "Object.h"

using namespace std;

Object::Object(World *W, float h, bool s) : world(W), height(h), shadow(s)
{
    setSize(32.f);
}

void Object::init()
{
}

void Object::setSize(float s)
{
    size = s;

    float alfSize = size / 2.f;

    shape.clear();

    p1 = Point(-alfSize, height, -alfSize);
    p2 = Point( alfSize, height, -alfSize);
    p3 = Point( alfSize, height,  alfSize);
    p4 = Point(-alfSize, height,  alfSize);

    // FACE TOP
    shape.addTriangle(&p1, &p2, &p3);
    shape.addTriangle(&p3, &p4, &p1);

    if (height > 0.f)
    {
        p5 = Point(-alfSize, 0.f,  alfSize);
        p6 = Point( alfSize, 0.f,  alfSize);
        p7 = Point( alfSize, 0.f, -alfSize);
        p8 = Point(-alfSize, 0.f, -alfSize);

        // FACE FRONT LEFT
        shape.addTriangle(&p5, &p4, &p3);
        shape.addTriangle(&p3, &p6, &p5);

        // FACE FRONT RIGHT
        shape.addTriangle(&p6, &p3, &p2);
        shape.addTriangle(&p2, &p7, &p6);

        // FACE BACK LEFT
        shape.addTriangle(&p1, &p4, &p5);
        shape.addTriangle(&p5, &p8, &p1);

        // FACE BACK RIGHT
        shape.addTriangle(&p2, &p1, &p8);
        shape.addTriangle(&p8, &p7, &p2);

        // FACE BOTTOM
        shape.addTriangle(&p5, &p6, &p7);
        shape.addTriangle(&p7, &p8, &p5);
    }

    shape.updateConnectivity();
}

void Object::setPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void Object::draw()
{
    shape.draw();
}

void Object::drawOutline()
{
    glColor4f(1.f, 1.f, 1.f, 0.02);

    shape.drawOutline();
}

void Object::updateShadows(Light *l)
{
    if (shadow && height > 0.f)
    {
        //if (l->getIntensityAtPosition(position) > 0.01f)
        //{
        //}

        shape.updateShadows(l->getPosition() - position);
    }
}

void Object::drawShadow(Light *l)
{
    shape.drawShadow(l->getPosition() - position);
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

