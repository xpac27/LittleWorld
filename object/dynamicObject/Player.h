#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "../DynamicObject.h"

#include <iostream>

class Player : public DynamicObject
{
    public:

        Player();
        virtual void init();
        virtual void draw();
        virtual void update(float time);
};

#endif

