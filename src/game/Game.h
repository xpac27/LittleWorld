#ifndef DEF_GAME
#define DEF_GAME

#include "../resources/Conf.h"
#include "../resources/Notifications.h"
#include "../scene/World.h"

#include <SFML/System/Randomizer.hpp>
#include <iostream>

class Game
{
    public:

        Game();

        void init();
        void draw();
        void update(float time);
        void onEvent(sf::Event *event);
        void setMousePosition(unsigned int x, unsigned int y);


    private:

        World world;

        float windowScale;
        float windowPaddingLeft;
        float windowPaddingTop;
};

#endif

