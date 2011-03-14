#ifndef DEF_STATICOBJECT
#define DEF_STATICOBJECT

#include "../Object.h"

class World;

class StaticObject : public Object
{
    public:

        int getGridX();
        int getGridY();


    protected:

        StaticObject(World *w, float h);
};

#endif

