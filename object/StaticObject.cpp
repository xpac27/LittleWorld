#include "StaticObject.h"

StaticObject::StaticObject(World *w, float h, bool s) : Object(w, h)
{
    solid = s;
}

int StaticObject::getGridX()
{
    return position.getGridX();
}

int StaticObject::getGridY()
{
    return position.getGridY();
}

bool StaticObject::isWalkable()
{
    return !solid;
}

