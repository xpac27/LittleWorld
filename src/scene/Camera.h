#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "Light.h"
#include "Object.h"
#include "../math/Vector3.h"
#include "../resources/Conf.h"

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

class Camera
{
    public:

        Camera();

        void update(float time);
        void draw(std::list<Object*> *objects, std::list<Light*> *lights);
        void setFocus(Object *o);

        float getX();
        float getY();
        float getZ();


    private:

        Object* focus;

        Vector3 position;

        float speed;
        float tolerance;
        float inertia;
};

#endif

