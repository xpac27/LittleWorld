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

    if (width / height > Conf::SCREEN_WIDTH / Conf::SCREEN_HEIGHT)
    {
        glOrtho
        (
            Conf::SCREEN_WIDTH / -2.f + ((width - Conf::SCREEN_WIDTH) / -2.f),
            Conf::SCREEN_WIDTH / 2.f + ((width - Conf::SCREEN_WIDTH) / 2.f),
            Conf::SCREEN_HEIGHT / -2.f,
            Conf::SCREEN_HEIGHT / 2.f,
            -1000.f,
            1000.f
        );
    }
    else
    {
        glOrtho
        (
            Conf::SCREEN_WIDTH / -2.f,
            Conf::SCREEN_WIDTH / 2.f,
            Conf::SCREEN_HEIGHT / -2.f + ((height - Conf::SCREEN_HEIGHT) / -2.f),
            Conf::SCREEN_HEIGHT / 2.f + ((height - Conf::SCREEN_HEIGHT) / 2.f),
            -1000.f,
            1000.f
        );
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main()
{
    // Create main window
    WindowSettings Settings;
    Settings.AntialiasingLevel = 4;
    Settings.StencilBits = 8;
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
    glOrtho(Conf::SCREEN_WIDTH / -2.f, Conf::SCREEN_WIDTH / 2.f, Conf::SCREEN_HEIGHT / -2.f, Conf::SCREEN_HEIGHT / 2.f, -1000.f, 1000.f);
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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset matix
        glLoadIdentity();

        glRotatef(35.264, 1.0, 0.0, 0.0);
        glRotatef(-45.0, 0.0, 1.0, 0.0);

        //Update
        game.update(clock.GetElapsedTime());
        clock.Reset();

        // Draw...
        game.draw();

        glBegin(GL_LINES);
        glColor3d(40.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(40.0, 0.0, 0.0);
        glColor3d(0.0, 40.0, 0.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 40.0, 0.0);
        glColor3d(0.0, 0.0, 40.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 40.0);
        glEnd();

        // Finally, display the rendered frame on screen
        application.Display();
    }

    return EXIT_SUCCESS;
}

