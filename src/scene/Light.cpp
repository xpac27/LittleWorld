#include "Light.h"

Light::Light(float x, float y, float z, float r, float g, float b)
{
    red   = r;
    green = g;
    blue  = b;

    ca = 1.0f;
    la = 0.01f;
    qa = 0.0001f;

    setPosition(x, y, z);
}

void Light::setup()
{
    GLfloat LightPos[] = {0.f, 0.f, position.y, 1.f};
    GLfloat LightAmb[] = {red, green, blue, 0.f};
    GLfloat LightDif[] = {red, green, blue, 1.f};

    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, ca);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, la);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, qa);
}

void Light::setPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

float Light::getX()
{
    return position.x;
}

float Light::getY()
{
    return position.y;
}

float Light::getIntensityFromDistance(float distance)
{
    return 1 / (ca + la * distance + qa * pow(distance, 2));
}

float Light::getIntensityAtPosition(Vector3 p)
{
    return getIntensityFromDistance(Vector3Util::dist(position, p));
}

