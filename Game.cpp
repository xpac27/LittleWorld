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

    float height(0.f);
    //int r(0);

    for (unsigned int x(0); x < 10; x ++)
    {
        for (unsigned int y(0); y < 10; y ++)
        {
            //r = Randomizer::Random(0, 10);
            //height = ((r > 7) ? r - 6.f : 0.f) * 12.f;

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
        if ((float)event->Size.Width / (float)event->Size.Height > 800.f / 600.f)
        {
            windowScale = 600.f / event->Size.Height;
        }
        else
        {
            windowScale = 800.f / event->Size.Width;
        }
        windowPaddingLeft = ((float)event->Size.Width - (800.f / windowScale)) / -2.f;
        windowPaddingTop  = ((float)event->Size.Height - (600.f / windowScale)) / -2.f;
    }
}

void Game::setMousePosition(unsigned int x, unsigned int y)
{
    world.updateMousePosition((x + windowPaddingLeft) * windowScale, (y + windowPaddingTop) * windowScale);
}

