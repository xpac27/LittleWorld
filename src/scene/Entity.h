#ifndef DEF_ENTITY
#define DEF_ENTITY

#include "../math/Vector3.h"

#include <iostream>

class Entity
{
    public:

        Entity(float s);

        void setPosition(float x, float y, float z);
        void setLightned(bool v);

        bool isVisible();

        float getX();
        float getY();
        float getZ();
        float getHeight();
        float getSize();

        Vector3 getPosition();


    protected:

        float size;

        Vector3 position;


    private:

        bool visible;
        bool lightned;
};

#endif

