#include "Decor.h"

Decor::Decor(float x, float z, float s, bool w) : Static(s)
{
    position.x = x;
    position.y = 0.f;
    position.z = z;

    walkable = w;
}

bool Decor::isWalkable() { return walkable; }

