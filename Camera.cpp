#include "Camera.h"

using namespace std;

Camera::Camera()
{
    x         = 0.f;
    y         = 0.f;
    speed     = 50.f;
    tolerance = 50.f;
    inertia   = 0.3f;
}

void Camera::draw(Object* object)
{
    glPushMatrix();
    glTranslatef
    (
        y - x + 288.f + 400.f - 300.f,              // Origin is centered on the screen
        ((x + y - 400.f - 300.f) / -2.f) - 64.f,    // So minus alf screen width and height
        0.f
    );

    glPushMatrix();
    glTranslatef
    (
        // World to screen's X coordinate
        object->getX() - object->getY(),

        // World to screen's Y coordinate
        (object->getX() + object->getY()) / 2.0,

        // Z index is calc using screen's Y coord lowered to tiles screen height + object's index
        -100.f / (((object->getX() + object->getY()) / 2.0) / 64.f + object->getIndex())
    );

    object->draw();

    glPopMatrix();
    glPopMatrix();
}

void Camera::update(float time)
{
    if (x - focus->getX() > tolerance)
    {
        x -= (x - (focus->getX() + tolerance)) / (inertia / time);
    }
    else if (focus->getX() - x > tolerance)
    {
        x += ((focus->getX() - tolerance) - x) / (inertia / time);
    }

    if (y - focus->getY() > tolerance)
    {
        y -= (y - (focus->getY() + tolerance)) / (inertia / time);
    }
    else if (focus->getY() - y > tolerance)
    {
        y += ((focus->getY() - tolerance) - y) / (inertia / time);
    }
}

void Camera::setFocus(Object *o)
{
    focus = o;
}

float Camera::getX()
{
    return x;
}

float Camera::getY()
{
    return y;
}

