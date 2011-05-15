/************************************
*
* Author: vincent.cogne@gmail.com
*
************************************/

#include "Game.h"
#include "util/Conf.h"
#include "util/IntersectionFunctions.h"

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
    glClearDepth(1.0f);
    glClearStencil(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Setup an ortho projection
    glViewport(0, 0, Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, Conf::SCREEN_WIDTH, Conf::SCREEN_HEIGHT, 0.f, 0.f, 100.f);
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Reset matix
        glLoadIdentity();

        //Update
        game.update(clock.GetElapsedTime());
        clock.Reset();

        // Draw...
        game.draw();



        //float x1, y1, x2, y2, x3, y3, x4, y4;
        //x1 = 10.f;
        //y1 = 10.f;
        //x2 = 300.f;
        //y2 = 300.f;
        //x3 = 140.f;
        //y3 = 40.f;
        //x4 = 10.f;
        //y4 = 400.f;

        //glColor4f(0.6f, 0.6f, 0.6f, 1.f);

        //glBegin(GL_LINES);
            //glVertex2f(x1, y1);
            //glVertex2f(x2, y2);
        //glEnd();

        //glBegin(GL_LINES);
            //glVertex2f(x3, y3);
            //glVertex2f(x4, y4);
        //glEnd();

        //IntersectionObject result;
        //result = IntersectionFunctions::LineSegmentToLineSegmentIntersection(x1, y1, x2, y2, x3, y3, x4, y4);
        //std::cout << result.NumberOfSolutions() << std::endl;
        //if (result.NumberOfSolutions() == 1)
        //{
            //std::cout << result.points[0].x << "x" << result.points[0].y << std::endl;
        //}


        // Finally, display the rendered frame on screen
        application.Display();
    }

    return EXIT_SUCCESS;
}

