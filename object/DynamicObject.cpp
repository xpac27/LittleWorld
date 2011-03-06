#include "DynamicObject.h"

DynamicObject::DynamicObject(World *w, float h) : Object(w, h)
{
}

void DynamicObject::update(float time)
{
}

void DynamicObject::remove()
{
}

void DynamicObject::move(float time)
{
    position.x += direction.getX() * speed * time;
    position.y += direction.getY() * speed * time;
}

