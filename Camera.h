#ifndef DEF_CAMERA
#define DEF_CAMERA

#include "Object.h"
#include "util/Position.h"
#include "util/Conf.h"

#include <SFML/Graphics.hpp>
#include <iostream>

class Camera
{
    public:

        Camera();

        void update(float time);
        void draw(Object* object);
        void drawShadow(Object* object);
        void setFocus(Object *o);
        void toScreenPosition(Position *p);

        float getX();
        float getY();



    private:

        Object* focus;

        Position position;

        float speed;
        float tolerance;
        float inertia;
};

#endif

