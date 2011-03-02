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


    protected:

        World *world;

        float x;
        float y;
        float size;
};

#endif

