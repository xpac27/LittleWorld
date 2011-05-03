#include "Game.h"

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
        e->setPosition(Randomizer::Random(0, Conf::WORLD_WIDTH), Randomizer::Random(0, Conf::WORLD_HEIGHT));
        world.addDynamicObject(e);
    }

    float height(0.f);
    int r(0);

    for (unsigned int x(0); x < Conf::WORLD_WIDTH / 64; x ++)
    {
        for (unsigned int y(0); y < Conf::WORLD_HEIGHT / 64; y ++)
        {
            r = Randomizer::Random(0, 20);
            //height = ((r > 17) ? r - 17.f : 0.f) * 12.f;
            height = ((r > 17) ? 5.f : 0.f) * 12.f;

            world.addStaticObject(new Tile(&world, x * 64.f, y * 64.f, height));
        }
    }
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
            world.ON_MOUSE_LEFT_DOWN();
        }
    }
    // RESIZE
    else if (event->Type == Event::Resized)
    {
        if ((float)event->Size.Width / (float)event->Size.Height > Conf::SCREEN_WIDTH / Conf::SCREEN_HEIGHT)
        {
            windowScale = Conf::SCREEN_HEIGHT / event->Size.Height;
        }
        else
        {
            windowScale = Conf::SCREEN_WIDTH / event->Size.Width;
        }
        windowPaddingLeft = ((float)event->Size.Width - (Conf::SCREEN_WIDTH / windowScale)) / -2.f;
        windowPaddingTop  = ((float)event->Size.Height - (Conf::SCREEN_HEIGHT / windowScale)) / -2.f;
    }
}

void Game::setMousePosition(unsigned int x, unsigned int y)
{
    world.updateMousePosition((x + windowPaddingLeft) * windowScale, (y + windowPaddingTop) * windowScale);
}

