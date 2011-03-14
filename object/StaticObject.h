#ifndef DEF_STATICOBJECT
#define DEF_STATICOBJECT

#include "../Object.h"

class World;

class StaticObject : public Object
{
    public:

        StaticObject(World *w, float h, bool s);

        int getGridX();
        int getGridY();

        bool isWalkable();


    protected:

        StaticObject(World *w, float h);


    private:

        bool solid;
};

#endif

