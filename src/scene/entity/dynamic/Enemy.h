#ifndef DEF_ENEMY
#define DEF_ENEMY

#include "../Dynamic.h"
#include "../../World.h"

#include <SFML/System/Randomizer.hpp>
#include <iostream>

class Enemy : public Dynamic
{
    public:

        Enemy(World *W, float s);

        virtual void update(float time);
};

#endif

