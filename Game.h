#ifndef DEF_GAME
#define DEF_GAME

#include "World.h"
#include "object/dynamicObject/Player.h"

class Game
{
    public:

        Game();

        void draw();
        void update(float time);


    private:

        World world;
};

#endif

