/************************************
*
* Author: vincent.cogne@gmail.com
*
************************************/

#include "Game.h"
#include "util/Conf.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

void onWindowResized(float width, float height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float space;

    if (width / height > 800.f / 600.f)
    {
        space = abs(((600.f / (height / width)) - 800.f) / 2.f);
        glOrtho(-1.f * space, 800.f + space, 600.f, 0.f, 0.f, 100.f);
    }
    else
    {
        space = abs(((800.f / (width / height)) - 600.f) / 2.f);
        glOrtho(0.f, 800.f, 600.f + space, -1.f * space, 0.f, 100.f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main()
{
    // Create main window
    WindowSettings Settings;
    //Settings.AntialiasingLevel = 4;
    RenderWindow application(VideoMode(800, 600), "Game", (Style::Close | Style::Resize), Settings);
    application.PreserveOpenGLStates(true);
    application.UseVerticalSync(true);

    // Setup rendering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Setup an ortho projection
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, 800.f, 600.f, 0.f, 0.f, 100.f);
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

        // Clear depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

