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

    // FACE TOP
    shape.addTriangle
    (
        -alfSize, height, -alfSize,
         alfSize, height, -alfSize,
         alfSize, height,  alfSize
    );
    shape.addTriangle
    (
         alfSize, height,  alfSize,
        -alfSize, height,  alfSize,
        -alfSize, height, -alfSize
    );

    if (height > 0.f)
    {
        // FACE FRONT LEFT
        shape.addTriangle
        (
            -alfSize, 0.f,    alfSize,
            -alfSize, height, alfSize,
             alfSize, height, alfSize
        );
        shape.addTriangle
        (
             alfSize, height, alfSize,
             alfSize, 0.f,    alfSize,
            -alfSize, 0.f,    alfSize
        );

        // FACE FRONT RIGHT
        shape.addTriangle
        (
            alfSize, 0.f,     alfSize,
            alfSize, height,  alfSize,
            alfSize, height, -alfSize
        );
        shape.addTriangle
        (
            alfSize, height, -alfSize,
            alfSize, 0.f,    -alfSize,
            alfSize, 0.f,     alfSize
        );

        // FACE BACK LEFT
        shape.addTriangle
        (
            -alfSize, height, -alfSize,
            -alfSize, height,  alfSize,
            -alfSize, 0.f,     alfSize
        );
        shape.addTriangle
        (
            -alfSize, 0.f,     alfSize,
            -alfSize, 0.f,    -alfSize,
            -alfSize, height, -alfSize
        );

        // FACE BACK RIGHT
        shape.addTriangle
        (
             alfSize, height, -alfSize,
            -alfSize, height, -alfSize,
            -alfSize, 0.f,    -alfSize
        );
        shape.addTriangle
        (
            -alfSize, 0.f,    -alfSize,
             alfSize, 0.f,    -alfSize,
             alfSize, height, -alfSize
        );
    }
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
    glColor4f(1.f, 1.f, 1.f, 0.2);

    shape.drawOutline();
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

