#include "Light.h"

Light::Light(float x, float y, float h, float r, float g, float b)
{
    height = h;

    red   = r;
    green = g;
    blue  = b;

    ca = 1.0f;
    la = 0.01f;
    qa = 0.0001f;

    position.x = x;
    position.y = y;
}

void Light::setup()
{
    GLfloat LightPos[] = {0.f, 0.f, height, 1.f};
    GLfloat LightAmb[] = {red, green, blue, 0.f};
    GLfloat LightDif[] = {red, green, blue, 1.f};

    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, ca);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, la);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, qa);
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

float Light::getIntensityFromDistance(float distance)
{
    return 1 / (ca + la * distance + qa * pow(distance, 2));
}

float Light::getIntensityAtPosition(Vector2 p)
{
    return getIntensityFromDistance(Vector2::distance(position, p));
}

