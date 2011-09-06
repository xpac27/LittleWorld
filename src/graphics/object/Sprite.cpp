#include "Sprite.h"

using namespace std;

Sprite::Sprite(Entity *e, float size, float height, float red, float green, float blue, float alpha) : Object(e)
{
    totalVertex = 4;
    totalIndex  = 6;

    float alfSize = size / 2.f;

    vertexes[0].location[X_POS] = alfSize;
    vertexes[0].location[Y_POS] = height;
    vertexes[0].location[Z_POS] = -alfSize;
    vertexes[0].normal[X_POS]   = 0.f;
    vertexes[0].normal[Y_POS]   = height;
    vertexes[0].normal[Z_POS]   = 0.f;
    vertexes[0].tex[U_POS]      = 0.f;
    vertexes[0].tex[V_POS]      = 0.f;

    vertexes[1].location[X_POS] = -alfSize;
    vertexes[1].location[Y_POS] = height;
    vertexes[1].location[Z_POS] = -alfSize;
    vertexes[1].normal[X_POS]   = 0.f;
    vertexes[1].normal[Y_POS]   = height;
    vertexes[1].normal[Z_POS]   = 0.f;
    vertexes[1].tex[U_POS]      = 0.f;
    vertexes[1].tex[V_POS]      = height;

    vertexes[2].location[X_POS] = -alfSize;
    vertexes[2].location[Y_POS] = height;
    vertexes[2].location[Z_POS] = alfSize;
    vertexes[2].normal[X_POS]   = 0.f;
    vertexes[2].normal[Y_POS]   = height;
    vertexes[2].normal[Z_POS]   = 0.f;
    vertexes[2].tex[U_POS]      = alfSize;
    vertexes[2].tex[V_POS]      = height;

    vertexes[3].location[X_POS] = alfSize;
    vertexes[3].location[Y_POS] = height;
    vertexes[3].location[Z_POS] = alfSize;
    vertexes[3].normal[X_POS]   = 0.f;
    vertexes[3].normal[Y_POS]   = height;
    vertexes[3].normal[Z_POS]   = 0.f;
    vertexes[3].tex[U_POS]      = alfSize;
    vertexes[3].tex[V_POS]      = 0.f;

    index[0] = 0;
    index[1] = 1;
    index[2] = 2;

    index[3] = 2;
    index[4] = 3;
    index[5] = 0;

    for (int i = 0; i < 24; i++)
    {
        vertexes[i].color[0] = red;
        vertexes[i].color[1] = green;
        vertexes[i].color[2] = blue;
        vertexes[i].color[3] = alpha;
    }
}

void Sprite::draw()
{
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < totalIndex; i ++)
    {
        glColor4f(vertexes[index[i]].color[0], vertexes[index[i]].color[1], vertexes[index[i]].color[2], vertexes[index[i]].color[3]);
        glNormal3f(vertexes[index[i]].normal[0], vertexes[index[i]].normal[1], vertexes[index[i]].normal[2]);
        glVertex3f(vertexes[index[i]].location[0], vertexes[index[i]].location[1], vertexes[index[i]].location[2]);
    }
    glEnd();
}

void Sprite::outline()
{
    for (unsigned int i = 0; i < totalIndex; i ++)
    {
        if (i%3 == 0)
        {
            if (i != 0)
            {
                glEnd();
            }
            glBegin(GL_LINE_LOOP);
        }
        glColor4f(vertexes[index[i]].color[0], vertexes[index[i]].color[1], vertexes[index[i]].color[2], vertexes[index[i]].color[3]);
        glNormal3f(vertexes[index[i]].normal[0], vertexes[index[i]].normal[1], vertexes[index[i]].normal[2]);
        glVertex3f(vertexes[index[i]].location[0], vertexes[index[i]].location[1], vertexes[index[i]].location[2]);
    }
    glEnd();
}

