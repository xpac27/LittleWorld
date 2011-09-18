#include "Static.h"

Static::Static(float s) : Entity(s)
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

