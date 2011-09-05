#include "Static.h"

Static::Static(World *W, float s) : Entity(W, s)
{
}

int Static::getGridX()
{
    return floor((position.x + 64.f) / 128.f);
}

int Static::getGridY()
{
    return floor((position.y + 64.f) / 128.f);
}

int Static::getGridZ()
{
    return floor((position.z + 64.f) / 128.f);
}

