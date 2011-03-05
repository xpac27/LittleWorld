#ifndef DEF_OBJECT
#define DEF_OBJECT

#include <boost/bind.hpp>

class World;

class Object
{
    public:

        Object(World *w);

        virtual void init();
        virtual void draw();

        float getX();
        float getY();
        float getZ();


    protected:

        World *world;

        float x;
        float y;
        float z;
        float size;
};

#endif

