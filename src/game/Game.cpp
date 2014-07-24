#include "Game.h"

using namespace std;
using namespace sf;

Game::Game()
{
    windowScale       = 1.f;
    windowPaddingLeft = 0.f;
    windowPaddingTop  = 0.f;
}

void Game::init()
{
    world.addPlayer(true);

    for (unsigned int i = 0; i < 20; i ++)
    {
        world.addEnemy(float(RAND_FLOAT * WORLD_WIDTH), float(RAND_FLOAT * WORLD_HEIGHT));
    }

    world.addWallDecor(1.f * 128.f, 4.f * 128.f, 64.f);
    world.addWallDecor(2.f * 128.f, 10.f * 128.f, 24.f);
    world.addWallDecor(4.f * 128.f, 1.f * 128.f, 128.f);
    world.addWallDecor(8.f * 128.f, 7.f * 128.f, 32.f);
    world.addWallDecor(6.f * 128.f, 6.f * 128.f, 48.f);
    world.addWallDecor(5.f * 128.f, 6.f * 128.f, 96.f);
    world.addWallDecor(5.f * 128.f, 5.f * 128.f, 64.f);
    world.addWallDecor(5.f * 128.f, 8.f * 128.f, 64.f);
    world.addWallDecor(4.f * 128.f, 8.f * 128.f, 64.f);
    world.addWallDecor(12.f * 128.f, 8.f * 128.f, 24.f);
    world.addWallDecor(11.f * 128.f, 5.f * 128.f, 48.f);
    world.addWallDecor(15.f * 128.f, 10.f * 128.f, 32.f);
    world.addWallDecor(10.f * 128.f, 13.f * 128.f, 64.f);
    world.addWallDecor(8.f * 128.f, 16.f * 128.f, 32.f);
    for (unsigned int x(0); x < WORLD_WIDTH / 128; x ++)
    {
        for (unsigned int y(0); y < WORLD_HEIGHT / 128; y ++)
        {
            world.addFloorDecor(x * 128.f, y * 128.f);
        }
    }

    world.addLight(256.f, 128.f, 256.f, 1.f, 0.f, 0.f);    // 2x2
    world.addLight(1024.f, 120.f, 1024.f, 0.f, 1.f, 0.f);  // 8x8
    world.addLight(1280.f, 120.f, 512.f, 0.f, 0.f, 1.f);   // 10x4
    world.addLight(640.f, 120.f, 512.f, 1.f, 1.f, 1.f);    // 5x4
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
    if (event->type == Event::MouseButtonPressed)
    {
        if (event->mouseButton.button == Mouse::Left)
        {
            world.dispatch(Notifications::ON_MOUSE_LEFT_DOWN);
        }
    }
    // RESIZE
    else if (event->type == Event::Resized)
    {
        world.dispatch(Notifications::ON_WINDOW_RESIZED);

        if ((float)event->size.width / (float)event->size.height > SCREEN_WIDTH / SCREEN_HEIGHT)
        {
            windowScale = SCREEN_HEIGHT / event->size.height;
        }
        else
        {
            windowScale = SCREEN_WIDTH / event->size.width;
        }
        windowPaddingLeft = ((float)event->size.width - (SCREEN_WIDTH / windowScale)) / -2.f;
        windowPaddingTop  = ((float)event->size.height - (SCREEN_HEIGHT / windowScale)) / -2.f;
        cout << windowScale << endl;
    }
}

void Game::setMousePosition(unsigned int x, unsigned int y)
{
    world.updateMousePosition((x + windowPaddingLeft) * windowScale - SCREEN_WIDTH / 2.f, (y + windowPaddingTop) * windowScale - SCREEN_HEIGHT / 2.f);
}

