#include "Camera.h"

using namespace std;

Camera::Camera()
{
    speed     = 50.f;
    tolerance = 50.f;
    inertia   = 0.3f;

    position.set(0.f, 0.f, 0.f);
}

void Camera::draw(Object* object)
{
    glPushMatrix();
    glTranslatef
    (
        position.y - position.x + 288.f + 400.f - 300.f,              // Origin is centered on the screen
        ((position.x + position.y - 400.f - 300.f) / -2.f) - 64.f,    // So minus alf screen width and height
        0.f
    );

    glPushMatrix();
    glTranslatef
    (
        // World to screen's X coordinate
        object->getX() - object->getY(),

        // World to screen's Y coordinate
        (object->getX() + object->getY()) / 2.f,

        // Z index is calc using screen's Y coord lowered to tiles screen height + object's index
        -100.f / (((object->getX() + object->getY()) / 2.f) / 64.f + object->getIndex())
    );

    object->draw();

    glPopMatrix();
    glPopMatrix();
}

void Camera::update(float time)
{
    if (position.x - focus->getX() > tolerance)
    {
        position.x -= (position.x - (focus->getX() + tolerance)) / (inertia / time);
    }
    else if (focus->getX() - position.x > tolerance)
    {
        position.x += ((focus->getX() - tolerance) - position.x) / (inertia / time);
    }

    if (position.y - focus->getY() > tolerance)
    {
        position.y -= (position.y - (focus->getY() + tolerance)) / (inertia / time);
    }
    else if (focus->getY() - position.y > tolerance)
    {
        position.y += ((focus->getY() - tolerance) - position.y) / (inertia / time);
    }
}

void Camera::toScreenPosition(Position *p)
{
    float nx = p->x;
    float ny = p->y;
    p->x = nx - ny;
    p->y = (nx + ny) / 2.f;
    p->x += position.y - position.x + 288.f + 400.f - 300.f;
    p->y += ((position.x + position.y - 400.f - 300.f) / -2.f) - 64.f;
}

void Camera::setFocus(Object *o)
{
    focus = o;
}

float Camera::getX()
{
    return position.x;
}

float Camera::getY()
{
    return position.y;
}

