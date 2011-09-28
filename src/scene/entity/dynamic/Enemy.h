#ifndef DEF_ENEMY
#define DEF_ENEMY

#include "../Dynamic.h"
#include "../../World.h"

#include <SFML/System/Randomizer.hpp>
#include <iostream>

class Enemy : public Dynamic
{
    public:

        Enemy(World *w, float x, float z, float s);

        virtual void update(float time);
};

#endif

