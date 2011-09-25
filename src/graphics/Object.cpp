#include "Object.h"

using namespace std;

Object::Object(Entity *e)
{
    entity = e;
    visible = false;
}

void Object::draw()
{
}

void Object::outline()
{
}

void Object::setVisibility(bool v)
{
    visible = v;
}

float Object::getX()    { return entity->getX(); }
float Object::getY()    { return entity->getY(); }
float Object::getZ()    { return entity->getZ(); }
float Object::getSize() { return entity->getSize(); }

bool Object::isVisible() { return visible; }

Vector3 Object::getPosition() { return entity->getPosition(); }

