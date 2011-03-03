#include "Game.h"

using namespace sf;

Game::Game(const Input &i) : input(i)
{
    world.addDynamicObject(new Player(&world));
}

void Game::draw()
{
    world.draw();
}

void Game::update(float time)
{
    world.update(time);
}

void Game::onEvent(Event *event)
{
    if ((*event).Type == Event::MouseButtonPressed)
    {
        if ((*event).MouseButton.Button == Mouse::Left)
        {
            world.ON_MOUSE_LEFT_DOWN();
        }
    }
}

