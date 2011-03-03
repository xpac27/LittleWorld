#ifndef DEF_GAME
#define DEF_GAME

#include "World.h"
#include "object/dynamicObject/Player.h"

#include <SFML/System.hpp>

class Game
{
    public:

        Game(const sf::Input &i);

        void draw();
        void update(float time);
        void onEvent(sf::Event *event);


    private:

        const sf::Input &input;

        World world;
};

#endif

