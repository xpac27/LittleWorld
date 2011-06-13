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

        void drawAll(std::list<Object*> *objects);
        void outlineAll(std::list<Object*> *objects);
        void drawAllShadows(std::list<Object*> *objects, Light *l);
        void updateAllShadows(std::list<Object*> *objects, Light *l);
        void translateObject(Object *o);
        void setupLight(Light *l);

        Object* focus;

        Vector3 position;

        float speed;
        float tolerance;
        float inertia;
};

#endif

