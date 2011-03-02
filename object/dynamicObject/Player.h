#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "../DynamicObject.h"
#include "../../World.h"

#include <boost/bind.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public DynamicObject
{
    public:

        Player(World *w);

        virtual void init();
        virtual void draw();
        virtual void update(float time);

        void prout();
};

#endif

