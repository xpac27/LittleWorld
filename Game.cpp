#include "Game.h"

Game::Game()
{
    world.addDynamicObject(new Player(&world));
    world.ON_TEST();
}

void Game::draw()
{
    world.draw();
}

void Game::update(float time)
{
    world.update(time);
}

