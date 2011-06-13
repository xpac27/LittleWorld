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

void setupWindow(float width, float height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float space;

    if (width / height > Conf::SCREEN_WIDTH / Conf::SCREEN_HEIGHT)
    {
        space = abs(((Conf::SCREEN_HEIGHT / (height / width)) - Conf::SCREEN_WIDTH) / 2.f);
        glOrtho
        (
            Conf::SCREEN_WIDTH / -2.f - space,
            Conf::SCREEN_WIDTH / 2.f + space,
            Conf::SCREEN_HEIGHT / -2.f,
            Conf::SCREEN_HEIGHT / 2.f,
            -1000.f,
            1000.f
        );
    }
    else
    {
        space = abs(((Conf::SCREEN_WIDTH / (width / height)) - Conf::SCREEN_HEIGHT) / 2.f);
        glOrtho
        (
            Conf::SCREEN_WIDTH / -2.f,
            Conf::SCREEN_WIDTH / 2.f,
            Conf::SCREEN_HEIGHT / -2.f - space,
            Conf::SCREEN_HEIGHT / 2.f + space,
            -1000.f,
            1000.f
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
    setupWindow(Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT);

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

        // Isometric angle
        glRotatef(30.f, 1.f, 0.f, 0.f);
        glRotatef(-45.f, 0.f, 1.f, 0.f);

        // Scale
        glScaled(sqrt(1/2.0), sqrt(1/3.0), sqrt(1/2.0));

        //Update
        game.update(clock.GetElapsedTime());
        clock.Reset();

        // Draw...
        game.draw();

        glBegin(GL_LINES);
        glColor3d(1.f, 0.f, 0.f);
        glVertex3d(0.f, 0.f, 0.f);
        glVertex3d(50.f, 0.f, 0.f);
        glColor3d(0.f, 1.f, 0.f);
        glVertex3d(0.f, 0.f, 0.f);
        glVertex3d(0.f, 50.f, 0.f);
        glColor3d(0.f, 0.f, 1.f);
        glVertex3d(0.f, 0.f, 0.f);
        glVertex3d(0.f, 0.f, 50.f);
        glEnd();

        // Finally, display the rendered frame on screen
        application.Display();
    }

    return EXIT_SUCCESS;
}

