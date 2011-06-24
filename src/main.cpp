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
    WindowSettings Settings;
    Settings.AntialiasingLevel = 4;
    Settings.StencilBits = 8;
    RenderWindow application(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game", (Style::Close | Style::Resize), Settings);
    application.PreserveOpenGLStates(true);
    application.UseVerticalSync(false);
    application.SetFramerateLimit(0);

    // Setup rendering
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_LINE_SMOOTH);
    //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

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

    // Gather a pointer to the input system
    const Input& input = application.GetInput();

    // Create a clocks for measuring the time elapsed
    Clock gameClock;
    Clock clock;

    // Create the game object
    Game game(input);
    game.init();

    // Start game loop
    while (application.IsOpened())
    {
        // Give the game mouse screen related's position
        game.setMousePosition(input.GetMouseX(), input.GetMouseY());

        // Process events
        Event event;
        while (application.GetEvent(event))
        {
            // Close window : exit
            if (event.Type == Event::KeyPressed && event.Key.Code == Key::Escape)
            {
                application.Close();
            }

            switch (event.Type)
            {
                case Event::Closed:
                    application.Close();
                    break;

                case Event::Resized:
                    game.onEvent(&event);
                    onWindowResized(event.Size.Width, event.Size.Height);
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
                case Event::JoyButtonPressed:
                case Event::JoyButtonReleased:
                case Event::JoyMoved:
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
        game.update(gameClock.GetElapsedTime());
        gameClock.Reset();

        // Framerate
        frameCount ++;
        if (clock.GetElapsedTime() >= 1.f)
        {
            std::cout << "Framerate: " << (frameCount * clock.GetElapsedTime()) << " FPS" << std::endl;
            frameCount = 0;
            clock.Reset();
        }

        // Draw...
        game.draw();

        // Finally, display the rendered frame on screen
        application.Display();
    }

    return EXIT_SUCCESS;
}

