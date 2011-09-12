#include "Sprite.h"

using namespace std;

Sprite::Sprite(Entity *e, float size, float height, float red, float green, float blue, float alpha) : Object(e)
{
    totalVertex = 4;
    totalIndexes  = 6;

    float alfSize = size / 2.f;

    vertices[0].location[X_POS] = alfSize;
    vertices[0].location[Y_POS] = height;
    vertices[0].location[Z_POS] = -alfSize;
    vertices[0].normal[X_POS]   = 0.f;
    vertices[0].normal[Y_POS]   = 1.f;
    vertices[0].normal[Z_POS]   = 0.f;
    vertices[0].tex[U_POS]      = 0.f;
    vertices[0].tex[V_POS]      = 0.f;

    vertices[1].location[X_POS] = -alfSize;
    vertices[1].location[Y_POS] = height;
    vertices[1].location[Z_POS] = -alfSize;
    vertices[1].normal[X_POS]   = 0.f;
    vertices[1].normal[Y_POS]   = 1.f;
    vertices[1].normal[Z_POS]   = 0.f;
    vertices[1].tex[U_POS]      = 0.f;
    vertices[1].tex[V_POS]      = height;

    vertices[2].location[X_POS] = -alfSize;
    vertices[2].location[Y_POS] = height;
    vertices[2].location[Z_POS] = alfSize;
    vertices[2].normal[X_POS]   = 0.f;
    vertices[2].normal[Y_POS]   = 1.f;
    vertices[2].normal[Z_POS]   = 0.f;
    vertices[2].tex[U_POS]      = alfSize;
    vertices[2].tex[V_POS]      = height;

    vertices[3].location[X_POS] = alfSize;
    vertices[3].location[Y_POS] = height;
    vertices[3].location[Z_POS] = alfSize;
    vertices[3].normal[X_POS]   = 0.f;
    vertices[3].normal[Y_POS]   = 1.f;
    vertices[3].normal[Z_POS]   = 0.f;
    vertices[3].tex[U_POS]      = alfSize;
    vertices[3].tex[V_POS]      = 0.f;

    indexes[0] = 0;
    indexes[1] = 1;
    indexes[2] = 2;

    indexes[3] = 2;
    indexes[4] = 3;
    indexes[5] = 0;

    for (int i = 0; i < totalVertex; i++)
    {
        vertices[i].color[0] = red;
        vertices[i].color[1] = green;
        vertices[i].color[2] = blue;
        vertices[i].color[3] = alpha;
    }

    #if USE_VBO
    vertexBufferObject = new VBO(totalVertex, totalIndexes);
    vertexBufferObject->uploadVertices(vertices, indexes);
    #endif
}

void Sprite::draw()
{
    #if USE_VBO
    vertexBufferObject->draw();
    #else
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < totalIndexes; i ++)
    {
        glColor4f(vertices[indexes[i]].color[0], vertices[indexes[i]].color[1], vertices[indexes[i]].color[2], vertices[indexes[i]].color[3]);
        glNormal3f(vertices[indexes[i]].normal[0], vertices[indexes[i]].normal[1], vertices[indexes[i]].normal[2]);
        glVertex3f(vertices[indexes[i]].location[0], vertices[indexes[i]].location[1], vertices[indexes[i]].location[2]);
    }
    glEnd();
    #endif
}

void Sprite::outline()
{
    for (unsigned int i = 0; i < totalIndexes; i ++)
    {
        if (i%3 == 0)
        {
            if (i != 0)
            {
                glEnd();
            }
            glBegin(GL_LINE_LOOP);
        }
        glColor4f(vertices[indexes[i]].color[0], vertices[indexes[i]].color[1], vertices[indexes[i]].color[2], vertices[indexes[i]].color[3]);
        glNormal3f(vertices[indexes[i]].normal[0], vertices[indexes[i]].normal[1], vertices[indexes[i]].normal[2]);
        glVertex3f(vertices[indexes[i]].location[0], vertices[indexes[i]].location[1], vertices[indexes[i]].location[2]);
    }
    glEnd();
}

