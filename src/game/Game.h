#ifndef DEF_GAME
#define DEF_GAME

#include "../scene/World.h"
#include "../scene/object/dynamicObject/Player.h"
#include "../scene/object/dynamicObject/Enemy.h"
#include "../scene/object/staticObject/Tile.h"
#include "../resources/Conf.h"

#include <SFML/System/Randomizer.hpp>
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

