#ifndef DEF_OBJECT
#define DEF_OBJECT

#include <SFML/Graphics.hpp>
#include <boost/bind.hpp>

class World;

class Object
{
    public:

        Object(World *w, float h);

        virtual void init();
        virtual void draw();

        float getX();
        float getY();
        float getHeight();
        float getSize();
        float getIndex();


    protected:

        World *world;

        float x;
        float y;
        float size;
        float alfSize;
        float quarterSize;

    private:

        float index;
        float height;
};

#endif

