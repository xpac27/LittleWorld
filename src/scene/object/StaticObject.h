#ifndef DEF_STATICOBJECT
#define DEF_STATICOBJECT

#include "../Object.h"

class World;

class StaticObject : public Object
{
    public:

        StaticObject(World *W, float h, bool w, bool s);

        int getGridX();
        int getGridY();

        bool isWalkable();


    protected:

        StaticObject(World *w, float h);


    private:

        bool walkable;
};

#endif

