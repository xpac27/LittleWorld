#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "../DynamicObject.h"
#include "../../World.h"

#include <SFML/Graphics.hpp>
#include <boost/bind.hpp>
#include <iostream>

class Player : public DynamicObject
{
    public:

        Player(World *w);

        virtual void init();
        virtual void draw();
        virtual void update(float time);


    private:

        void onMouseLeftDown();
};

#endif

