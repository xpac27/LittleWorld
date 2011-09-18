#include "Entity.h"

using namespace std;

Entity::Entity(float s) : size(s)
{
    visible  = false;
    lightned = false;
}

void Entity::setPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void Entity::setLightned(bool v)   { lightned = v; }

float Entity::getX()               { return position.x; }
float Entity::getY()               { return position.y; }
float Entity::getZ()               { return position.z; }
float Entity::getSize()            { return size; }

bool Entity::isVisible()           { return visible; }

Vector3 Entity::getPosition()      { return position; }

