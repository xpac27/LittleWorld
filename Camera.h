#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "Object.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class Camera
{
    public:

        Camera();

        void update(float time);
        void draw(Object* object);
        void setFocus(Object *o);

        float getX();
        float getY();


    private:

        Object* focus;

        float x;
        float y;
        float speed;
        float tolerance;
        float inertia;
};

#endif

