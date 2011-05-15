#ifndef DEF_ENEMY
#define DEF_ENEMY

#include "../DynamicObject.h"
#include "../../util/Position.h"
#include "../../World.h"

#include <SFML/System/Randomizer.hpp>
#include <boost/bind.hpp>
#include <iostream>

class Enemy : public DynamicObject
{
    public:

        Enemy(World *W);

        virtual void draw();
        virtual void update(float time);
};

#endif

