#include "Light.h"

Light::Light(float x, float y, float h, float r, float g, float b)
{
    height = h;

    // TODO Create a class for color
    red   = r;
    green = g;
    blue  = b;

    position.x = x;
    position.y = y;
}

void Light::setup()
{
    GLfloat LightPos[] = {0.f, 0.f, height, 1.f};
    GLfloat LightAmb[] = {0.f, 0.f, 0.f, 0.f};
    GLfloat LightDif[] = {red, green, blue, 1.f};

    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);
}

void Light::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

float Light::getX()
{
    return position.x;
}

float Light::getY()
{
    return position.y;
}

float Light::getHeight()
{
    return height;
}

