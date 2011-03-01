#include "Game.h"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
    // Create main window
    RenderWindow application(VideoMode(800, 600), "Game");
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
    glOrtho(0, 800, 600, 0, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Create a clock for measuring the time elapsed
    Clock clock;

    // Create the game object
    Game::instance()->init();

    // Start game loop
    while (application.IsOpened())
    {
        // Process events
        Event Event;
        while (application.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == Event::Closed)
            {
                application.Close();
            }

            // Escape key : exit
            if ((Event.Type == Event::KeyPressed) && (Event.Key.Code == Key::Escape))
            {
                application.Close();
            }

            // Adjust the viewport when the window is resized
            if (Event.Type == Event::Resized)
            {
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();

                float space;

                if ((float)Event.Size.Width / (float)Event.Size.Height > 800.f / 600.f)
                {
                    space = abs(((600.f / ((float)Event.Size.Height / (float)Event.Size.Width)) - 800.f) / 2.f);
                    glOrtho(-1.f * space, 800.f + space, 600.f, 0.f, 0.f, 100.f);
                }
                else
                {
                    space = abs(((800.f / ((float)Event.Size.Width / (float)Event.Size.Height)) - 600.f) / 2.f);
                    glOrtho(0.f, 800.f, 600.f + space, -1.f * space, 0.f, 100.f);
                }

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
            }
        }

        // Clear depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Update
        Game::instance()->update(clock.GetElapsedTime());
        clock.Reset();

        // Draw...
        Game::instance()->draw();

        // Finally, display the rendered frame on screen
        application.Display();
    }

    return EXIT_SUCCESS;
}

