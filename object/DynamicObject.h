#ifndef DEF_DYNAMICOBJECT
#define DEF_DYNAMICOBJECT

#include "../Object.h"
#include "../util/Position.h"
#include "../util/Direction.h"

#include <iostream>

class World;

class DynamicObject : public Object
{
    public:

        DynamicObject(World *w, float h);

        virtual void update(float time);
        virtual void remove();

        void move(float time);


    protected:

        float speed;

        Direction direction;
};

#endif

