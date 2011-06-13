#include "Game.h"

using namespace std;
using namespace sf;

Game::Game(const Input &i) : input(i)
{
    windowScale       = 1.f;
    windowPaddingLeft = 0.f;
    windowPaddingTop  = 0.f;
}

void Game::init()
{
    Player *p = new Player(&world);

    world.addDynamicObject(p);
    world.setFocus(p);

    for (unsigned int i = 0; i < 20; i ++)
    {
        Enemy *e = new Enemy(&world);
        e->setPosition(Randomizer::Random(0, Conf::WORLD_WIDTH), 0.f, Randomizer::Random(0, Conf::WORLD_HEIGHT));
        world.addDynamicObject(e);
    }

    float height(0.f);
    int r(0);

    for (unsigned int x(0); x < Conf::WORLD_WIDTH / 128; x ++)
    {
        for (unsigned int y(0); y < Conf::WORLD_HEIGHT / 128; y ++)
        {
            //r = Randomizer::Random(0, 20);
            //height = ((r > 18) ? Randomizer::Random(1, 8) : 0.f) * 24.f;
            world.addStaticObject(new Tile(&world, x * 128.f, 0.f, y * 128.f, height));
        }
    }

    //world.addLight(new Light(256.f, 128.f, 256.f, 1.f, 0.f, 0.f));
    //world.addLight(new Light(1024.f, 120.f, 1024.f, 0.f, 1.f, 0.f));
    //world.addLight(new Light(1280.f, 120.f, 512.f, 0.f, 0.f, 1.f));
    world.addLight(new Light(720.f, 120.f, 512.f, 1.f, 1.f, 1.f));
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
    // MOUSE
    if (event->Type == Event::MouseButtonPressed)
    {
        if (event->MouseButton.Button == Mouse::Left)
        {
            world.dispatch(World::ON_MOUSE_LEFT_DOWN);
        }
    }
    // RESIZE
    else if (event->Type == Event::Resized)
    {
        if ((float)event->Size.Width / (float)event->Size.Height > Conf::SCREEN_WIDTH / Conf::SCREEN_HEIGHT)
        {
            windowScale= Conf::SCREEN_HEIGHT / event->Size.Height;
        }
        else
        {
            windowScale= Conf::SCREEN_WIDTH / event->Size.Width;
        }
        windowPaddingLeft = ((float)event->Size.Width - (Conf::SCREEN_WIDTH / windowScale)) / -2.f;
        windowPaddingTop  = ((float)event->Size.Height - (Conf::SCREEN_HEIGHT / windowScale)) / -2.f;
    }
}

void Game::setMousePosition(unsigned int x, unsigned int y)
{
    world.updateMousePosition((x + windowPaddingLeft) * windowScale - Conf::SCREEN_WIDTH / 2.f, (y + windowPaddingTop) * windowScale - Conf::SCREEN_HEIGHT / 2.f);
}

