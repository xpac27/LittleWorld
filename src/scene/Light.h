#ifndef DEF_LIGHT
#define DEF_LIGHT

#include "../graphics/Vector2.h"

#include <SFML/Graphics.hpp>

class Light
{
    public:

        Light(float x, float y, float h, float r, float g, float b);

        void setup();

        void setPosition(float x, float y);

        float getX();
        float getY();
        float getHeight();
        float getIntensityFromDistance(float d);
        float getIntensityAtPosition(Vector2 p);


    private:

        float height;
        float red;
        float green;
        float blue;
        float ca;
        float la;
        float qa;

        Vector2 position;
};

#endif


