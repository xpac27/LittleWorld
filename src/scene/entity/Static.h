#ifndef DEF_STATIC
#define DEF_STATIC

#include "../Entity.h"

class World;

class Static : public Entity
{
    public:

        Static(World *W, float s);

        int getGridX();
        int getGridY();
        int getGridZ();


    private:

        bool walkable;
};

#endif

