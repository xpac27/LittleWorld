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

void onWindowResized(float width, float height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float space;

    if (width / height > Conf::SCREEN_WIDTH / Conf::SCREEN_HEIGHT)
    {
        space = abs(((Conf::SCREEN_HEIGHT / (height / width)) - Conf::SCREEN_WIDTH) / 2.f);
        glOrtho(-1.f * space, Conf::SCREEN_WIDTH + space, Conf::SCREEN_HEIGHT, 0.f, 0.f, 100.f);
    }
    else
    {
        space = abs(((Conf::SCREEN_WIDTH / (width / height)) - Conf::SCREEN_HEIGHT) / 2.f);
        glOrtho(0.f, Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT + space, -1.f * space, 0.f, 100.f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main()
{
    // Create main window
    WindowSettings Settings;
    Settings.AntialiasingLevel = 4;
    RenderWindow application(VideoMode(Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT), "Game", (Style::Close | Style::Resize), Settings);
    application.PreserveOpenGLStates(true);
    application.UseVerticalSync(true);

    // Setup rendering
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_LINE_SMOOTH);
    //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearDepth(GL_ONE);
    glClearStencil(GL_ZERO);
    glDepthFunc(GL_LEQUAL);
    glClearColor(GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO);

    // Setup an ortho projection
    glViewport(0.f, 0.f, Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT, 0.f, 0.f, 1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Gather a pointer to the input system
    const Input& input = application.GetInput();

    // Create a clock for measuring the time elapsed
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

        //Update
        game.update(clock.GetElapsedTime());
        clock.Reset();

        // Draw...
        game.draw();

        // Finally, display the rendered frame on screen
        application.Display();
    }

    return EXIT_SUCCESS;
}

