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
        e->setPosition(Randomizer::Random(0, WORLD_WIDTH), 0.f, Randomizer::Random(0, WORLD_HEIGHT));
        world.addDynamicObject(e);
    }

    for (unsigned int x(0); x < WORLD_WIDTH / 128; x ++)
    {
        for (unsigned int y(0); y < WORLD_HEIGHT / 128; y ++)
        {
            world.addStaticObject(new Tile(&world, x * 128.f, 0.f, y * 128.f, 0.f));
        }
    }

    world.addStaticObject(new Tile(&world, 1.f * 128.f, 0.f, 4.f * 128.f, 64.f));
    world.addStaticObject(new Tile(&world, 2.f * 128.f, 0.f, 10.f * 128.f, 24.f));
    world.addStaticObject(new Tile(&world, 4.f * 128.f, 0.f, 1.f * 128.f, 128.f));
    world.addStaticObject(new Tile(&world, 8.f * 128.f, 0.f, 7.f * 128.f, 32.f));
    world.addStaticObject(new Tile(&world, 6.f * 128.f, 0.f, 6.f * 128.f, 48.f));
    world.addStaticObject(new Tile(&world, 5.f * 128.f, 0.f, 6.f * 128.f, 96.f));
    world.addStaticObject(new Tile(&world, 5.f * 128.f, 0.f, 5.f * 128.f, 64.f));
    world.addStaticObject(new Tile(&world, 5.f * 128.f, 0.f, 8.f * 128.f, 64.f));
    world.addStaticObject(new Tile(&world, 4.f * 128.f, 0.f, 8.f * 128.f, 64.f));
    world.addStaticObject(new Tile(&world, 12.f * 128.f, 0.f, 8.f * 128.f, 24.f));
    world.addStaticObject(new Tile(&world, 11.f * 128.f, 0.f, 5.f * 128.f, 48.f));
    world.addStaticObject(new Tile(&world, 15.f * 128.f, 0.f, 10.f * 128.f, 32.f));
    world.addStaticObject(new Tile(&world, 10.f * 128.f, 0.f, 13.f * 128.f, 64.f));
    world.addStaticObject(new Tile(&world, 8.f * 128.f, 0.f, 16.f * 128.f, 32.f));

    world.addLight(new Light(256.f, 128.f, 256.f, 1.f, 0.f, 0.f));    // 2x2
    world.addLight(new Light(1024.f, 120.f, 1024.f, 0.f, 1.f, 0.f));  // 8x8
    world.addLight(new Light(1280.f, 120.f, 512.f, 0.f, 0.f, 1.f));   // 10x4
    world.addLight(new Light(640.f, 120.f, 512.f, 1.f, 1.f, 1.f));    // 5x4
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
        world.dispatch(World::ON_WINDOW_RESIZED);

        if ((float)event->Size.Width / (float)event->Size.Height > SCREEN_WIDTH / SCREEN_HEIGHT)
        {
            windowScale = SCREEN_HEIGHT / event->Size.Height;
        }
        else
        {
            windowScale = SCREEN_WIDTH / event->Size.Width;
        }
        windowPaddingLeft = ((float)event->Size.Width - (SCREEN_WIDTH / windowScale)) / -2.f;
        windowPaddingTop  = ((float)event->Size.Height - (SCREEN_HEIGHT / windowScale)) / -2.f;
        cout << windowScale << endl;
    }
}

void Game::setMousePosition(unsigned int x, unsigned int y)
{
    world.updateMousePosition((x + windowPaddingLeft) * windowScale - SCREEN_WIDTH / 2.f, (y + windowPaddingTop) * windowScale - SCREEN_HEIGHT / 2.f);
}

