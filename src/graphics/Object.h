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

        void setVisibility(bool v);

        float getX();
        float getY();
        float getZ();
        float getSize();

        bool isVisible();

        Vector3 getPosition();


    protected:

        Entity *entity;

        bool visible;
};

#endif

