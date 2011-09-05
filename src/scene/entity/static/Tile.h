#ifndef DEF_TILE
#define DEF_TILE

#include "../Static.h"
#include "../../World.h"

#include <iostream>

class Tile : public Static
{
    public:

        Tile(World *W, float x, float z, float s, bool w);

        bool isWalkable();


    protected:

        bool walkable;
};

#endif

