#ifndef DEF_LIGHT
#define DEF_LIGHT

#include "../Object.h"

#include <SFML/Graphics.hpp>

class Light : public Object
{
    public:

        Light(Entity *e, float r, float g, float b);

        void setup();

        float getIntensityFromDistance(float d);


    private:

        float red;
        float green;
        float blue;
        float ca;
        float la;
        float qa;
};

#endif


