#include <SFML/Graphics.hpp>
#include <iostream>
#include "Dummy.h"

int main()
{
    // Create main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "Game");
    App.PreserveOpenGLStates(true);
    App.UseVerticalSync(true);

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
    sf::Clock Clock;

    int const dummyNumber(10000);
    Dummy dummyList[dummyNumber];

    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
            {
                App.Close();
            }

            // Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            {
                App.Close();
            }

            // Adjust the viewport when the window is resized
            if (Event.Type == sf::Event::Resized)
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
        for (int i(0); i < dummyNumber; i ++)
        {
            dummyList[i].update(Clock.GetElapsedTime());
        }
        Clock.Reset();

        // Draw...
        for (int i(0); i < dummyNumber; i ++)
        {
            dummyList[i].draw();
        }

        //glPushMatrix();
        //glTranslatef(0.f, 0.f, 0.0f);
        //glColor4f(1.f, 1.f, 1.f, 0.5f);
        //glBegin(GL_QUADS);
            //glVertex2f(0.f,   0.f);
            //glVertex2f(0.f,   600.f);
            //glVertex2f(800.f, 600.f);
            //glVertex2f(800.f, 0.f);
        //glEnd();
        //glPopMatrix();

        //glPushMatrix();
        //glTranslatef(400.f, 300.f, 0.0f);
        //glColor4f(1.f, 1.f, 0.f, 0.5f);
        //glBegin(GL_QUADS);
            //glVertex2f(-15.f, -15.f);
            //glVertex2f(-15.f,  15.f);
            //glVertex2f( 15.f,  15.f);
            //glVertex2f( 15.f, -15.f);
        //glEnd();
        //glPopMatrix();

        //glPushMatrix();
        //glTranslatef(10.f, 10.f, 0.0f);
        //glColor4f(1.f, 0.f, 0.f, 0.5f);
        //glBegin(GL_QUADS);
            //glVertex2f(-10.f, -10.f);
            //glVertex2f(-10.f,  10.f);
            //glVertex2f( 10.f,  10.f);
            //glVertex2f( 10.f, -10.f);
        //glEnd();
        //glPopMatrix();

        // Finally, display the rendered frame on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}

