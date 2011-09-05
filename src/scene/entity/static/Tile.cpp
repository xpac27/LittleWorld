#include "Tile.h"

Tile::Tile(World *W, float x, float y, float z, float s, bool w) : Static(W, s)
{
    position.x = x;
    position.y = y;
    position.z = z;

    walkable = w;
}

bool Tile::isWalkable() { return walkable; }

