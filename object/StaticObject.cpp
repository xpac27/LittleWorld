#include "StaticObject.h"

StaticObject::StaticObject(World *W, float h, bool w, bool s) : Object(W, h, s)
{
    walkable = w;
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
    return walkable;
}
