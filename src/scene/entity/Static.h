#ifndef DEF_STATIC
#define DEF_STATIC

#include "../Entity.h"

class Static : public Entity
{
    public:

        Static(float s);

        int getGridX();
        int getGridY();
        int getGridZ();


    private:

        bool walkable;
};

#endif

