#ifndef DEF_GAME
#define DEF_GAME

#include "World.h"
#include "object/dynamicObject/Player.h"
#include "object/staticObject/Tile.h"

#include <SFML/System.hpp>
#include <iostream>

class Game
{
    public:

        Game(const sf::Input &i);

        void init();
        void draw();
        void update(float time);
        void onEvent(sf::Event *event);
        void setMousePosition(unsigned int x, unsigned int y);


    private:

        const sf::Input &input;

        World world;

        float windowScale;
        float windowPaddingLeft;
        float windowPaddingTop;
};

#endif

