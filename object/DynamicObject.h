#ifndef DEF_DYNAMICOBJECT
#define DEF_DYNAMICOBJECT

#include "../Object.h"

#include <iostream>

class World;

class DynamicObject : public Object
{
    public:

        DynamicObject(World *w);
        virtual void update(float time);
        virtual void remove();


    protected:

        float speed;
};

#endif

