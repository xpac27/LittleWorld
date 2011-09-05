#ifndef DEF_OBJECT
#define DEF_OBJECT

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


    private:

        Entity *entity;
};

#endif

