#ifndef DEF_OBJECT
#define DEF_OBJECT

#include "../math/Vector3.h"
#include "../scene/Entity.h"

#include <iostream>

class Object
{
    public:

        Object(Entity *e);

        virtual void draw();
        virtual void outline();

        float getX();
        float getY();
        float getZ();
        float getSize();

        Vector3 getPosition();


    protected:

        Entity *entity;
};

#endif

