#include "Game.h"

using namespace std;

Game::Game() {}

void Game::init()
{
    this->addDynamicObject(new Player());
}

void Game::draw()
{
    std::list<DynamicObject*>::iterator i = this->dynamicObjectList.begin();
    do
    {
        (*i)->draw();
        i ++;
    }
    while (i != this->dynamicObjectList.end());
}

void Game::update(float time)
{
    std::list<DynamicObject*>::iterator i = this->dynamicObjectList.begin();
    do
    {
        (*i)->update(time);
        i ++;
    }
    while (i != this->dynamicObjectList.end());
}

void Game::addDynamicObject(DynamicObject *o)
{
    o->init();
    this->dynamicObjectList.push_back(o);
}

