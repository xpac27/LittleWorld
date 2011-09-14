#ifndef DEF_DECOR
#define DEF_DECOR

#include "../Static.h"
#include "../../World.h"

#include <iostream>

class Decor : public Static
{
    public:

        Decor(World *W, float x, float z, float s, bool w);

        bool isWalkable();


    protected:

        bool walkable;
};

#endif

