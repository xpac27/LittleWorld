#include "StaticObject.h"

StaticObject::StaticObject(World *W, float h, bool w, bool s) : Object(W, h, s)
{
    walkable = w;
}

int StaticObject::getGridX()
{
    return floor((position.x + 32.f) / 64.f);
}

int StaticObject::getGridY()
{
    return floor((position.y + 32.f) / 64.f);
}

int StaticObject::getGridZ()
{
    return floor((position.z + 32.f) / 64.f);
}

bool StaticObject::isWalkable()
{
    return walkable;
}
