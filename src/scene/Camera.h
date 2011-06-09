#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "Light.h"
#include "Object.h"
#include "../graphics/Vector2.h"
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
        void toScreenPosition(Vector2 *p);

        float getX();
        float getY();


    private:

        void translateCamera();
        void translateObject(Object *o);
        void translateLight(Light *l);
        void translate(float x, float y, float h, float i);

        Object* focus;

        Vector2 position;

        float speed;
        float tolerance;
        float inertia;
};

#endif

