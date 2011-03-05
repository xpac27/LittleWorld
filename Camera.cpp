#include "Camera.h"

using namespace std;

Camera::Camera()
{
    x = 0.f;
    y = 0.f;
    speed = 50.f;
    tolerance = 50.f;
}

void Camera::draw(Object* object)
{
    glPushMatrix();
    glTranslatef(-x, -y, 0.f);

        glPushMatrix();
        glTranslatef(object->getX(), object->getY(), object->getZ() - 100.f);

        object->draw();

        glPopMatrix();
    glPopMatrix();
}

void Camera::update()
{
    if (x - focus->getX() + 400.f > tolerance)
    {
        x = focus->getX() - 400.f + tolerance;
    }
    else if (focus->getX() - x - 400.f > tolerance)
    {
        x = focus->getX() - 400.f - tolerance;
    }

    if (y - focus->getY() + 300.f > tolerance)
    {
        y = focus->getY() - 300.f + tolerance;
    }
    else if (focus->getY() - y - 300.f > tolerance)
    {
        y = focus->getY() - 300.f - tolerance;
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

