#include "Game.h"

Game::Game()
{
    world.addDynamicObject(new Player(&world));
    world.ON_TEST();
}

void Game::draw()
{
    this->world.draw();
}

void Game::update(float time)
{
    this->world.update(time);
}

