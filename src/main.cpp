/************************************
*
* Author: vincent.cogne@gmail.com
*
************************************/

#include "game/Game.h"
#include "resources/Conf.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

float frameCount = 0.f;

void setupWindow(float width, float height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float space;

    if (width / height > SCREEN_WIDTH / SCREEN_HEIGHT)
    {
        // TODO compute back and front clip plane better
        space = abs(((SCREEN_HEIGHT / (height / width)) - SCREEN_WIDTH) / 2.f);
        glOrtho
        (
            SCREEN_WIDTH / -2.f - space,
            SCREEN_WIDTH / 2.f + space,
            SCREEN_HEIGHT / -2.f,
            SCREEN_HEIGHT / 2.f,
            SCREEN_HEIGHT * (SCREEN_HEIGHT / height) * -1,
            SCREEN_HEIGHT
        );
    }
    else
    {
        space = abs(((SCREEN_WIDTH / (width / height)) - SCREEN_HEIGHT) / 2.f);
        glOrtho
        (
            SCREEN_WIDTH / -2.f,
            SCREEN_WIDTH / 2.f,
            SCREEN_HEIGHT / -2.f - space,
            SCREEN_HEIGHT / 2.f + space,
            SCREEN_HEIGHT * (SCREEN_WIDTH / width) * -1.f,
            SCREEN_HEIGHT
        );
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void onWindowResized(float width, float height)
{
    setupWindow(width, height);
}

int main()
{
    // Create main window
    ContextSettings Settings;
    Settings.antialiasingLevel = 4;
    Settings.stencilBits = 8;
    RenderWindow application(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game", (Style::Close | Style::Resize), Settings);
    application.setVerticalSyncEnabled(false);
    application.setFramerateLimit(0);

    // Setup rendering
    glShadeModel(GL_SMOOTH);
    glCullFace(GL_FRONT);
    //glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_LINE_SMOOTH);
    //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Vertex buffer objects
    #if USE_VBO
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    #endif

    // Default values
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_FALSE);
    glColorMask(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    // Clear values
    glClearDepth(GL_ONE);
    glClearStencil(GL_ZERO);
    glClearColor(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    // Setup window
    setupWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Create a clocks for measuring the time elapsed
    Clock gameClock;
    Clock clock;

    // Create the game object
    Game game;
    game.init();

    // Start game loop
    while (application.isOpen())
    {
        // Give the game mouse screen related's position
        game.setMousePosition(Mouse::getPosition(application).x, Mouse::getPosition(application).y);

        // Process events
        Event event;
        while (application.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                application.close();
            }

            switch (event.type)
            {
                case Event::Closed:
                    application.close();
                    break;

                case Event::Resized:
                    game.onEvent(&event);
                    onWindowResized(event.size.width, event.size.height);
                    break;

                case Event::MouseButtonPressed:
                    game.onEvent(&event);
                    break;

                case Event::LostFocus:
                case Event::GainedFocus:
                case Event::TextEntered:
                case Event::KeyPressed:
                case Event::KeyReleased:
                case Event::MouseWheelMoved:
                case Event::MouseButtonReleased:
                case Event::MouseMoved:
                case Event::MouseEntered:
                case Event::MouseLeft:
                case Event::JoystickConnected:
                case Event::JoystickDisconnected:
                case Event::JoystickButtonPressed:
                case Event::JoystickButtonReleased:
                case Event::JoystickMoved:
                case Event::Count:
                    break;
            }
        }

        // Reset matix
        glLoadIdentity();

        // Isometric angle
        glRotatef(30.f, 1.f, 0.f, 0.f);
        glRotatef(-45.f, 0.f, 1.f, 0.f);

        // Scale
        glScaled(sqrt(1/2.0), sqrt(1/3.0), sqrt(1/2.0));

        //Update
        game.update(gameClock.getElapsedTime().asSeconds());
        gameClock.restart();

        // Framerate
        frameCount ++;
        if (clock.getElapsedTime().asSeconds() >= 1.f)
        {
            std::cout << "Framerate: " << (frameCount * clock.getElapsedTime().asSeconds()) << " FPS" << std::endl;
            frameCount = 0;
            clock.restart();
        }

        //Draw...
        game.draw();

        // Finally, display the rendered frame on screen
        application.display();
    }

    return EXIT_SUCCESS;
}

