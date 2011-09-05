#ifndef DEF_ENTITY
#define DEF_ENTITY

#include "../math/Vector3.h"

#include <iostream>

class World;

class Entity
{
    public:

        Entity(World *W, float s);

        void setPosition(float x, float y, float z);
        void setVisibility(bool v);
        void setLightned(bool v);

        bool isVisible();
        bool isLightned();

        float getX();
        float getY();
        float getZ();
        float getHeight();
        float getSize();

        Vector3 getPosition();


    protected:

        World *world;

        float size;

        Vector3 position;


    private:

        bool visible;
        bool lightned;
};

#endif

