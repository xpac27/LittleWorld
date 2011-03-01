#include "Game.h"

// global static pointer used to ensure a single instance of the class.
Game* Game::p_instance = NULL;

Game::Game()
{
}

Game::Game(const Game &game)
{
}

Game& Game::operator=(const Game &game)
{
    return *this;
}

Game* Game::instance()
{
    if (!p_instance)
    {
        p_instance = new Game;
    }

    return p_instance;
}

void Game::init()
{
    this->addDynamicObject(new Player());
}

void Game::draw()
{
    std::list<DynamicObject*>::iterator i;
    for (i = this->dynamicObjectList.begin(); i != this->dynamicObjectList.end(); ++ i)
    {
        (*i)->draw();
    }
}

void Game::update(float time)
{
    std::list<DynamicObject*>::iterator i;
    for (i = this->dynamicObjectList.begin(); i != this->dynamicObjectList.end(); ++ i)
    {
        (*i)->update(time);
    }
}

void Game::addDynamicObject(DynamicObject *o)
{
    o->init();
    this->dynamicObjectList.push_back(o);
}

