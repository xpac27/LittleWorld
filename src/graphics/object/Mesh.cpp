#include "Mesh.h"

using namespace std;

Mesh::Mesh(Entity *e, float size, float height, float red, float green, float blue, float alpha) : Object(e)
{
    totalVertex = 24;
    totalTriangles = 12;
    totalIndexes = 36;

    float alfSize = size / 2.f;

    // Top
    vertices[0].location[X_POS]  = alfSize;
    vertices[0].location[Y_POS]  = height;
    vertices[0].location[Z_POS]  = -alfSize;
    vertices[0].normal[X_POS]    = 0.f;
    vertices[0].normal[Y_POS]    = 1.f;
    vertices[0].normal[Z_POS]    = 0.f;
    vertices[0].tex[U_POS]       = 0.f;
    vertices[0].tex[V_POS]       = 0.f;

    vertices[1].location[X_POS]  = -alfSize;
    vertices[1].location[Y_POS]  = height;
    vertices[1].location[Z_POS]  = -alfSize;
    vertices[1].normal[X_POS]    = 0.f;
    vertices[1].normal[Y_POS]    = 1.f;
    vertices[1].normal[Z_POS]    = 0.f;
    vertices[1].tex[U_POS]       = 0.f;
    vertices[1].tex[V_POS]       = height;

    vertices[2].location[X_POS]  = -alfSize;
    vertices[2].location[Y_POS]  = height;
    vertices[2].location[Z_POS]  = alfSize;
    vertices[2].normal[X_POS]    = 0.f;
    vertices[2].normal[Y_POS]    = 1.f;
    vertices[2].normal[Z_POS]    = 0.f;
    vertices[2].tex[U_POS]       = alfSize;
    vertices[2].tex[V_POS]       = height;

    vertices[3].location[X_POS]  = alfSize;
    vertices[3].location[Y_POS]  = height;
    vertices[3].location[Z_POS]  = alfSize;
    vertices[3].normal[X_POS]    = 0.f;
    vertices[3].normal[Y_POS]    = 1.f;
    vertices[3].normal[Z_POS]    = 0.f;
    vertices[3].tex[U_POS]       = alfSize;
    vertices[3].tex[V_POS]       = 0.f;

    // Bottom
    vertices[4].location[X_POS]  = alfSize;
    vertices[4].location[Y_POS]  = 0.f;
    vertices[4].location[Z_POS]  = alfSize;
    vertices[4].normal[X_POS]    = 0.f;
    vertices[4].normal[Y_POS]    = 0.f;
    vertices[4].normal[Z_POS]    = 0.f;
    vertices[4].tex[U_POS]       = 0.f;
    vertices[4].tex[V_POS]       = 0.f;

    vertices[5].location[X_POS]  = -alfSize;
    vertices[5].location[Y_POS]  = 0.f;
    vertices[5].location[Z_POS]  = alfSize;
    vertices[5].normal[X_POS]    = 0.f;
    vertices[5].normal[Y_POS]    = 0.f;
    vertices[5].normal[Z_POS]    = 0.f;
    vertices[5].tex[U_POS]       = 0.f;
    vertices[5].tex[V_POS]       = height;

    vertices[6].location[X_POS]  = -alfSize;
    vertices[6].location[Y_POS]  = 0.f;
    vertices[6].location[Z_POS]  = -alfSize;
    vertices[6].normal[X_POS]    = 0.f;
    vertices[6].normal[Y_POS]    = 0.f;
    vertices[6].normal[Z_POS]    = 0.f;
    vertices[6].tex[U_POS]       = alfSize;
    vertices[6].tex[V_POS]       = height;

    vertices[7].location[X_POS]  = alfSize;
    vertices[7].location[Y_POS]  = 0.f;
    vertices[7].location[Z_POS]  = -alfSize;
    vertices[7].normal[X_POS]    = 0.f;
    vertices[7].normal[Y_POS]    = 0.f;
    vertices[7].normal[Z_POS]    = 0.f;
    vertices[7].tex[U_POS]       = alfSize;
    vertices[7].tex[V_POS]       = 0.f;

    // Front
    vertices[8].location[X_POS]  = alfSize;
    vertices[8].location[Y_POS]  = height;
    vertices[8].location[Z_POS]  = alfSize;
    vertices[8].normal[X_POS]    = 0.f;
    vertices[8].normal[Y_POS]    = 0.f;
    vertices[8].normal[Z_POS]    = 1.f;
    vertices[8].tex[U_POS]       = 0.f;
    vertices[8].tex[V_POS]       = 0.f;

    vertices[9].location[X_POS]  = -alfSize;
    vertices[9].location[Y_POS]  = height;
    vertices[9].location[Z_POS]  = alfSize;
    vertices[9].normal[X_POS]    = 0.f;
    vertices[9].normal[Y_POS]    = 0.f;
    vertices[9].normal[Z_POS]    = 1.f;
    vertices[9].tex[U_POS]       = 0.f;
    vertices[9].tex[V_POS]       = height;

    vertices[10].location[X_POS] = -alfSize;
    vertices[10].location[Y_POS] = 0.f;
    vertices[10].location[Z_POS] = alfSize;
    vertices[10].normal[X_POS]   = 0.f;
    vertices[10].normal[Y_POS]   = 0.f;
    vertices[10].normal[Z_POS]   = 1.f;
    vertices[10].tex[U_POS]      = alfSize;
    vertices[10].tex[V_POS]      = height;

    vertices[11].location[X_POS] = alfSize;
    vertices[11].location[Y_POS] = 0.f;
    vertices[11].location[Z_POS] = alfSize;
    vertices[11].normal[X_POS]   = 0.f;
    vertices[11].normal[Y_POS]   = 0.f;
    vertices[11].normal[Z_POS]   = 1.f;
    vertices[11].tex[U_POS]      = alfSize;
    vertices[11].tex[V_POS]      = 0.f;

    // Back
    vertices[12].location[X_POS] = alfSize;
    vertices[12].location[Y_POS] = 0.f;
    vertices[12].location[Z_POS] = -alfSize;
    vertices[12].normal[X_POS]   = 0.f;
    vertices[12].normal[Y_POS]   = 0.f;
    vertices[12].normal[Z_POS]   = -1.f;
    vertices[12].tex[U_POS]      = 0.f;
    vertices[12].tex[V_POS]      = 0.f;

    vertices[13].location[X_POS] = -alfSize;
    vertices[13].location[Y_POS] = 0.f;
    vertices[13].location[Z_POS] = -alfSize;
    vertices[13].normal[X_POS]   = 0.f;
    vertices[13].normal[Y_POS]   = 0.f;
    vertices[13].normal[Z_POS]   = -1.f;
    vertices[13].tex[U_POS]      = 0.f;
    vertices[13].tex[V_POS]      = height;

    vertices[14].location[X_POS] = -alfSize;
    vertices[14].location[Y_POS] = height;
    vertices[14].location[Z_POS] = -alfSize;
    vertices[14].normal[X_POS]   = 0.f;
    vertices[14].normal[Y_POS]   = 0.f;
    vertices[14].normal[Z_POS]   = -1.f;
    vertices[14].tex[U_POS]      = alfSize;
    vertices[14].tex[V_POS]      = height;

    vertices[15].location[X_POS] = alfSize;
    vertices[15].location[Y_POS] = height;
    vertices[15].location[Z_POS] = -alfSize;
    vertices[15].normal[X_POS]   = 0.f;
    vertices[15].normal[Y_POS]   = 0.f;
    vertices[15].normal[Z_POS]   = -1.f;
    vertices[15].tex[U_POS]      = alfSize;
    vertices[15].tex[V_POS]      = 0.f;

    // Left
    vertices[16].location[X_POS] = -alfSize;
    vertices[16].location[Y_POS] = height;
    vertices[16].location[Z_POS] = alfSize;
    vertices[16].normal[X_POS]   = -alfSize;
    vertices[16].normal[Y_POS]   = 0.f;
    vertices[16].normal[Z_POS]   = 0.f;
    vertices[16].tex[U_POS]      = 0.f;
    vertices[16].tex[V_POS]      = 0.f;

    vertices[17].location[X_POS] = -alfSize;
    vertices[17].location[Y_POS] = height;
    vertices[17].location[Z_POS] = -alfSize;
    vertices[17].normal[X_POS]   = -1.f;
    vertices[17].normal[Y_POS]   = 0.f;
    vertices[17].normal[Z_POS]   = 0.f;
    vertices[17].tex[U_POS]      = 0.f;
    vertices[17].tex[V_POS]      = height;

    vertices[18].location[X_POS] = -alfSize;
    vertices[18].location[Y_POS] = 0.f;
    vertices[18].location[Z_POS] = -alfSize;
    vertices[18].normal[X_POS]   = -1.f;
    vertices[18].normal[Y_POS]   = 0.f;
    vertices[18].normal[Z_POS]   = 0.f;
    vertices[18].tex[U_POS]      = alfSize;
    vertices[18].tex[V_POS]      = height;

    vertices[19].location[X_POS] = -alfSize;
    vertices[19].location[Y_POS] = 0.f;
    vertices[19].location[Z_POS] = alfSize;
    vertices[19].normal[X_POS]   = -1.f;
    vertices[19].normal[Y_POS]   = 0.f;
    vertices[19].normal[Z_POS]   = 0.f;
    vertices[19].tex[U_POS]      = alfSize;
    vertices[19].tex[V_POS]      = 0.f;

    // Right
    vertices[20].location[X_POS] = alfSize;
    vertices[20].location[Y_POS] = height;
    vertices[20].location[Z_POS] = -alfSize;
    vertices[20].normal[X_POS]   = 1.f;
    vertices[20].normal[Y_POS]   = 0.f;
    vertices[20].normal[Z_POS]   = 0.f;
    vertices[20].tex[U_POS]      = 0.f;
    vertices[20].tex[V_POS]      = 0.f;

    vertices[21].location[X_POS] = alfSize;
    vertices[21].location[Y_POS] = height;
    vertices[21].location[Z_POS] = alfSize;
    vertices[21].normal[X_POS]   = 1.f;
    vertices[21].normal[Y_POS]   = 0.f;
    vertices[21].normal[Z_POS]   = 0.f;
    vertices[21].tex[U_POS]      = 0.f;
    vertices[21].tex[V_POS]      = height;

    vertices[22].location[X_POS] = alfSize;
    vertices[22].location[Y_POS] = 0.f;
    vertices[22].location[Z_POS] = alfSize;
    vertices[22].normal[X_POS]   = 1.f;
    vertices[22].normal[Y_POS]   = 0.f;
    vertices[22].normal[Z_POS]   = 0.f;
    vertices[22].tex[U_POS]      = alfSize;
    vertices[22].tex[V_POS]      = height;

    vertices[23].location[X_POS] = alfSize;
    vertices[23].location[Y_POS] = 0.f;
    vertices[23].location[Z_POS] = -alfSize;
    vertices[23].normal[X_POS]   = 1.f;
    vertices[23].normal[Y_POS]   = 0.f;
    vertices[23].normal[Z_POS]   = 0.f;
    vertices[23].tex[U_POS]      = alfSize;
    vertices[23].tex[V_POS]      = 0.f;

    // Index Array (define our triangles)
    triangles[0].vertexIndices[0] = indexes[0] = 0;
    triangles[0].vertexIndices[1] = indexes[1] = 1;
    triangles[0].vertexIndices[2] = indexes[2] = 2;

    triangles[1].vertexIndices[0] = indexes[3] = 2;
    triangles[1].vertexIndices[1] = indexes[4] = 3;
    triangles[1].vertexIndices[2] = indexes[5] = 0;

    triangles[2].vertexIndices[0] = indexes[6] = 4;
    triangles[2].vertexIndices[1] = indexes[7] = 5;
    triangles[2].vertexIndices[2] = indexes[8] = 6;

    triangles[3].vertexIndices[0] = indexes[9] = 6;
    triangles[3].vertexIndices[1] = indexes[10] = 7;
    triangles[3].vertexIndices[2] = indexes[11] = 4;

    triangles[4].vertexIndices[0] = indexes[12] = 8;
    triangles[4].vertexIndices[1] = indexes[13] = 9;
    triangles[4].vertexIndices[2] = indexes[14] = 10;

    triangles[5].vertexIndices[0] = indexes[15] = 10;
    triangles[5].vertexIndices[1] = indexes[16] = 11;
    triangles[5].vertexIndices[2] = indexes[17] = 8;

    triangles[6].vertexIndices[0] = indexes[18] = 12;
    triangles[6].vertexIndices[1] = indexes[19] = 13;
    triangles[6].vertexIndices[2] = indexes[20] = 14;

    triangles[7].vertexIndices[0] = indexes[21] = 14;
    triangles[7].vertexIndices[1] = indexes[22] = 15;
    triangles[7].vertexIndices[2] = indexes[23] = 12;

    triangles[8].vertexIndices[0] = indexes[24] = 16;
    triangles[8].vertexIndices[1] = indexes[25] = 17;
    triangles[8].vertexIndices[2] = indexes[26] = 18;

    triangles[9].vertexIndices[0] = indexes[27] = 18;
    triangles[9].vertexIndices[1] = indexes[28] = 19;
    triangles[9].vertexIndices[2] = indexes[29] = 16;

    triangles[10].vertexIndices[0] = indexes[30] = 20;
    triangles[10].vertexIndices[1] = indexes[31] = 21;
    triangles[10].vertexIndices[2] = indexes[32] = 22;

    triangles[11].vertexIndices[0] = indexes[33] = 22;
    triangles[11].vertexIndices[1] = indexes[34] = 23;
    triangles[11].vertexIndices[2] = indexes[35] = 20;

    // Colors
    for (int i = 0; i < totalVertex; i++)
    {
        vertices[i].color[0] = red;
        vertices[i].color[1] = green;
        vertices[i].color[2] = blue;
        vertices[i].color[3] = alpha;
    }

    updatePlaneEquations();
    updateConnectivity();

    #if USE_VBO
    vertexBufferObject = new VBO(totalVertex, totalIndexes);
    vertexBufferObject->uploadVertices(vertices, indexes);
    #endif
}

void Mesh::updatePlaneEquations()
{
    for (unsigned int i = 0; i < totalTriangles; i ++)
    {
        const Vertex& v1 = vertices[triangles[i].vertexIndices[0]];
        const Vertex& v2 = vertices[triangles[i].vertexIndices[1]];
        const Vertex& v3 = vertices[triangles[i].vertexIndices[2]];

        triangles[i].planeEquation.a = v1.location[1]*(v2.location[2]-v3.location[2])
                                     + v2.location[1]*(v3.location[2]-v1.location[2])
                                     + v3.location[1]*(v1.location[2]-v2.location[2]);
        triangles[i].planeEquation.b = v1.location[2]*(v2.location[0]-v3.location[0])
                                     + v2.location[2]*(v3.location[0]-v1.location[0])
                                     + v3.location[2]*(v1.location[0]-v2.location[0]);
        triangles[i].planeEquation.c = v1.location[0]*(v2.location[1]-v3.location[1])
                                     + v2.location[0]*(v3.location[1]-v1.location[1])
                                     + v3.location[0]*(v1.location[1]-v2.location[1]);
        triangles[i].planeEquation.d = -(v1.location[0]*(v2.location[1]*v3.location[2] - v3.location[1]*v2.location[2])
                                       + v2.location[0]*(v3.location[1]*v1.location[2] - v1.location[1]*v3.location[2])
                                       + v3.location[0]*(v1.location[1]*v2.location[2] - v2.location[1]*v1.location[2]));
    }
}

void Mesh::updateConnectivity()
{
    unsigned int p1i, p2i, p1j, p2j;
    unsigned int i, j, ki, kj;

    for (i = 0; i < totalTriangles; i ++)
    {
        for (ki = 0; ki < 3; ki++)
        {
            triangles[i].neighbourIndices[ki] = -1; // No Neighbors Set Up Yet
        }
    }

    for (i = 0; i < totalTriangles; i ++)
    {
        for (j = i + 1; j < totalTriangles; j ++)
        {
            for (ki = 0; ki < 3; ki++)
            {
                if (!triangles[i].neighbourIndices[ki])
                {
                    for (kj = 0; kj < 3; kj ++)
                    {
                        p1i = triangles[i].vertexIndices[ki];
                        p2i = triangles[i].vertexIndices[(ki + 1) % 3];
                        p1j = triangles[j].vertexIndices[kj];
                        p2j = triangles[j].vertexIndices[(kj + 1) % 3];

                        if ((p1i == p1j && p2i == p2j) || (p1i == p2j && p2i == p1j))
                        {
                            triangles[i].neighbourIndices[ki] = j + 1;
                            triangles[j].neighbourIndices[kj] = i + 1;
                        }
                    }
                }
            }
        }
    }
}

void Mesh::draw()
{
    #if USE_VBO
    vertexBufferObject->draw();
    #else
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < totalTriangles; i ++)
    {
        for (unsigned int v = 0; v < 3; v ++)
        {
            const Vertex& vertex = vertices[triangles[i].vertexIndices[v]];

            glColor4f(vertex.color[0], vertex.color[1], vertex.color[2], vertex.color[3]);
            glNormal3f(vertex.normal[0], vertex.normal[1], vertex.normal[2]);
            glVertex3f(vertex.location[0], vertex.location[1], vertex.location[2]);
        }
    }
    glEnd();
    #endif
}

void Mesh::outline()
{
    for (unsigned int i = 0; i < totalTriangles; i ++)
    {
        glBegin(GL_LINE_LOOP);
        for (unsigned int v = 0; v < 3; v ++)
        {
            const Vertex& vertex = vertices[triangles[i].vertexIndices[v]];

            glColor4f(vertex.color[0], vertex.color[1], vertex.color[2], vertex.color[3]);
            glNormal3f(vertex.normal[0], vertex.normal[1], vertex.normal[2]);
            glVertex3f(vertex.location[0], vertex.location[1], vertex.location[2]);
        }
        glEnd();
    }
}

void Mesh::drawShadow(Light *pLight)
{
    // TODO save shadow if light and mesh are linked to static entities

    unsigned int i, j, neighbourIndex;

    GLfloat lightPosition[3] =
    {
        pLight->getPosition().x - entity->getX(),
        pLight->getPosition().y - entity->getY(),
        pLight->getPosition().z - entity->getZ()
    };

    // Determine Which Faces Are Visible By The Light.
    for (i = 0; i < totalTriangles; i ++)
    {
        const Plane& plane = triangles[i].planeEquation;

        if (plane.a*lightPosition[0] + plane.b*lightPosition[1] + plane.c*lightPosition[2] + plane.d > 0)
        {
            triangles[i].visible = true;
        }
        else
        {
            triangles[i].visible = false;
        }
    }

    for (i = 0; i < totalTriangles; i ++)
    {
        const Triangle& triangle = triangles[i];

        if (triangle.visible)
        {
            // Go Through Each Edge
            for (j = 0; j < 3; j ++)
            {
                int neighbourIndex = triangle.neighbourIndices[j];

                // If Its Neighbouring Face Is Not Visible, Or There Is No Neighbour, Then This Edge Casts A Shadow
                if (triangles[neighbourIndex].visible == false || neighbourIndex == -1)
                {
                    // Get The Points On The Edge
                    const GLfloat *v1 = vertices[triangle.vertexIndices[j]].location;
                    const GLfloat *v2 = vertices[triangle.vertexIndices[(j + 1) % 3]].location;

                    // Calculate The Two Vertices In Distance
                    GLfloat v3[3];
                    GLfloat v4[3];

                    v3[0] = (v1[0] - lightPosition[0]) * 1000.f;
                    v3[1] = (v1[1] - lightPosition[1]) * 1000.f;
                    v3[2] = (v1[2] - lightPosition[2]) * 1000.f;

                    v4[0] = (v2[0] - lightPosition[0]) * 1000.f;
                    v4[1] = (v2[1] - lightPosition[1]) * 1000.f;
                    v4[2] = (v2[2] - lightPosition[2]) * 1000.f;

                    // Draw The Quadrilateral (As A Triangle Strip)
                    glBegin(GL_TRIANGLE_STRIP);
                    glVertex3f(v1[0], v1[1], v1[2]);
                    glVertex3f(v1[0] + v3[0], v1[1] + v3[1], v1[2] + v3[2]);
                    glVertex3f(v2[0], v2[1], v2[2]);
                    glVertex3f(v2[0] + v4[0], v2[1] + v4[1], v2[2] + v4[2]);
                    glEnd();
                }
            }
        }
    }
}

