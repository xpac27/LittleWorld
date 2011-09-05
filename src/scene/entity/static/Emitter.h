#ifndef DEF_EMITTER
#define DEF_EMITTER

#include "../Static.h"
#include "../../World.h"

#include <iostream>

class Emitter : public Static
{
    public:

        Emitter(World *W, float x, float y, float z);
};

#endif

