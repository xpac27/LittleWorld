#ifndef DEF_PLAYER
#define DEF_PLAYER

#include <iostream>
#include "../DynamicObject.h"

class Player : public DynamicObject
{
    public:

        Player();
        virtual void init();
        virtual void draw();
        virtual void update(float time);
};

#endif

