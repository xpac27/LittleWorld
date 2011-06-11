#ifndef DEF_LIGHT
#define DEF_LIGHT

#include "../math/Vector3.h"
#include "../math/Vector3Util.h"

#include <SFML/Graphics.hpp>

class Light
{
    public:

        Light(float x, float y, float z, float r, float g, float b);

        void setup();

        void setPosition(float x, float y, float z);

        float getX();
        float getY();
        float getIntensityFromDistance(float d);
        float getIntensityAtPosition(Vector3 p);


    private:

        float red;
        float green;
        float blue;
        float ca;
        float la;
        float qa;

        Vector3 position;
};

#endif


