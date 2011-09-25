#ifndef DEF_LIGHT
#define DEF_LIGHT

#include "../Object.h"
#include "../../math/Vector3.h"
#include "../../math/Vector3Util.h"

#include <SFML/Graphics.hpp>

class Light : public Object
{
    public:

        Light(Entity *e, float r, float g, float b);

        virtual void draw();
        virtual void outline();

        void setup();

        float getIntensityFromDistance(float d);
        float getIntensityAtPosition(Vector3 p);


    private:

        float red;
        float green;
        float blue;
        float ca;
        float la;
        float qa;
};

#endif


