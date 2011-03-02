#ifndef DEF_STATICOBJECT
#define DEF_STATICOBJECT

#include "../Object.h"

class World;

class StaticObject : public Object
{
    protected:

        StaticObject(World *w);
};

#endif

