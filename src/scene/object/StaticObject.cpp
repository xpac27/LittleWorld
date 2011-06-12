#include "StaticObject.h"

StaticObject::StaticObject(World *W, float h, bool w, bool s) : Object(W, h, s)
{
    walkable = w;
}

int StaticObject::getGridX()
{
    return floor((position.x + 64.f) / 128.f);
}

int StaticObject::getGridY()
{
    return floor((position.y + 64.f) / 128.f);
}

int StaticObject::getGridZ()
{
    return floor((position.z + 64.f) / 128.f);
}

bool StaticObject::isWalkable()
{
    return walkable;
}
