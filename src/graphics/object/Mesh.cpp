#include "Mesh.h"

using namespace std;

Mesh::Mesh(Entity *e, float size, float height, float red, float green, float blue, float alpha) : Object(e)
{
    totalVertex = 24;
    totalTriangles = 12;

    float alfSize = size / 2.f;

    // Top
    vertices[0].location[X_POS]  = alfSize;
    vertices[0].location[Y_POS]  = height;
    vertices[0].location[Z_POS]  = -alfSize;
    vertices[0].normal[X_POS]    = 0.f;
    vertices[0].normal[Y_POS]    = height;
    vertices[0].normal[Z_POS]    = 0.f;
    vertices[0].tex[U_POS]       = 0.f;
    vertices[0].tex[V_POS]       = 0.f;

    vertices[1].location[X_POS]  = -alfSize;
    vertices[1].location[Y_POS]  = height;
    vertices[1].location[Z_POS]  = -alfSize;
    vertices[1].normal[X_POS]    = 0.f;
    vertices[1].normal[Y_POS]    = height;
    vertices[1].normal[Z_POS]    = 0.f;
    vertices[1].tex[U_POS]       = 0.f;
    vertices[1].tex[V_POS]       = height;

    vertices[2].location[X_POS]  = -alfSize;
    vertices[2].location[Y_POS]  = height;
    vertices[2].location[Z_POS]  = alfSize;
    vertices[2].normal[X_POS]    = 0.f;
    vertices[2].normal[Y_POS]    = height;
    vertices[2].normal[Z_POS]    = 0.f;
    vertices[2].tex[U_POS]       = alfSize;
    vertices[2].tex[V_POS]       = height;

    vertices[3].location[X_POS]  = alfSize;
    vertices[3].location[Y_POS]  = height;
    vertices[3].location[Z_POS]  = alfSize;
    vertices[3].normal[X_POS]    = 0.f;
    vertices[3].normal[Y_POS]    = height;
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
    vertices[8].normal[Z_POS]    = alfSize;
    vertices[8].tex[U_POS]       = 0.f;
    vertices[8].tex[V_POS]       = 0.f;

    vertices[9].location[X_POS]  = -alfSize;
    vertices[9].location[Y_POS]  = height;
    vertices[9].location[Z_POS]  = alfSize;
    vertices[9].normal[X_POS]    = 0.f;
    vertices[9].normal[Y_POS]    = 0.f;
    vertices[9].normal[Z_POS]    = alfSize;
    vertices[9].tex[U_POS]       = 0.f;
    vertices[9].tex[V_POS]       = height;

    vertices[10].location[X_POS] = -alfSize;
    vertices[10].location[Y_POS] = 0.f;
    vertices[10].location[Z_POS] = alfSize;
    vertices[10].normal[X_POS]   = 0.f;
    vertices[10].normal[Y_POS]   = 0.f;
    vertices[10].normal[Z_POS]   = alfSize;
    vertices[10].tex[U_POS]      = alfSize;
    vertices[10].tex[V_POS]      = height;

    vertices[11].location[X_POS] = alfSize;
    vertices[11].location[Y_POS] = 0.f;
    vertices[11].location[Z_POS] = alfSize;
    vertices[11].normal[X_POS]   = 0.f;
    vertices[11].normal[Y_POS]   = 0.f;
    vertices[11].normal[Z_POS]   = alfSize;
    vertices[11].tex[U_POS]      = alfSize;
    vertices[11].tex[V_POS]      = 0.f;

    // Back
    vertices[12].location[X_POS] = alfSize;
    vertices[12].location[Y_POS] = 0.f;
    vertices[12].location[Z_POS] = -alfSize;
    vertices[12].normal[X_POS]   = 0.f;
    vertices[12].normal[Y_POS]   = 0.f;
    vertices[12].normal[Z_POS]   = -alfSize;
    vertices[12].tex[U_POS]      = 0.f;
    vertices[12].tex[V_POS]      = 0.f;

    vertices[13].location[X_POS] = -alfSize;
    vertices[13].location[Y_POS] = 0.f;
    vertices[13].location[Z_POS] = -alfSize;
    vertices[13].normal[X_POS]   = 0.f;
    vertices[13].normal[Y_POS]   = 0.f;
    vertices[13].normal[Z_POS]   = -alfSize;
    vertices[13].tex[U_POS]      = 0.f;
    vertices[13].tex[V_POS]      = height;

    vertices[14].location[X_POS] = -alfSize;
    vertices[14].location[Y_POS] = height;
    vertices[14].location[Z_POS] = -alfSize;
    vertices[14].normal[X_POS]   = 0.f;
    vertices[14].normal[Y_POS]   = 0.f;
    vertices[14].normal[Z_POS]   = -alfSize;
    vertices[14].tex[U_POS]      = alfSize;
    vertices[14].tex[V_POS]      = height;

    vertices[15].location[X_POS] = alfSize;
    vertices[15].location[Y_POS] = height;
    vertices[15].location[Z_POS] = -alfSize;
    vertices[15].normal[X_POS]   = 0.f;
    vertices[15].normal[Y_POS]   = 0.f;
    vertices[15].normal[Z_POS]   = -alfSize;
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
    vertices[17].normal[X_POS]   = -alfSize;
    vertices[17].normal[Y_POS]   = 0.f;
    vertices[17].normal[Z_POS]   = 0.f;
    vertices[17].tex[U_POS]      = 0.f;
    vertices[17].tex[V_POS]      = height;

    vertices[18].location[X_POS] = -alfSize;
    vertices[18].location[Y_POS] = 0.f;
    vertices[18].location[Z_POS] = -alfSize;
    vertices[18].normal[X_POS]   = -alfSize;
    vertices[18].normal[Y_POS]   = 0.f;
    vertices[18].normal[Z_POS]   = 0.f;
    vertices[18].tex[U_POS]      = alfSize;
    vertices[18].tex[V_POS]      = height;

    vertices[19].location[X_POS] = -alfSize;
    vertices[19].location[Y_POS] = 0.f;
    vertices[19].location[Z_POS] = alfSize;
    vertices[19].normal[X_POS]   = -alfSize;
    vertices[19].normal[Y_POS]   = 0.f;
    vertices[19].normal[Z_POS]   = 0.f;
    vertices[19].tex[U_POS]      = alfSize;
    vertices[19].tex[V_POS]      = 0.f;

    // Right
    vertices[20].location[X_POS] = alfSize;
    vertices[20].location[Y_POS] = height;
    vertices[20].location[Z_POS] = -alfSize;
    vertices[20].normal[X_POS]   = alfSize;
    vertices[20].normal[Y_POS]   = 0.f;
    vertices[20].normal[Z_POS]   = 0.f;
    vertices[20].tex[U_POS]      = 0.f;
    vertices[20].tex[V_POS]      = 0.f;

    vertices[21].location[X_POS] = alfSize;
    vertices[21].location[Y_POS] = height;
    vertices[21].location[Z_POS] = alfSize;
    vertices[21].normal[X_POS]   = alfSize;
    vertices[21].normal[Y_POS]   = 0.f;
    vertices[21].normal[Z_POS]   = 0.f;
    vertices[21].tex[U_POS]      = 0.f;
    vertices[21].tex[V_POS]      = height;

    vertices[22].location[X_POS] = alfSize;
    vertices[22].location[Y_POS] = 0.f;
    vertices[22].location[Z_POS] = alfSize;
    vertices[22].normal[X_POS]   = alfSize;
    vertices[22].normal[Y_POS]   = 0.f;
    vertices[22].normal[Z_POS]   = 0.f;
    vertices[22].tex[U_POS]      = alfSize;
    vertices[22].tex[V_POS]      = height;

    vertices[23].location[X_POS] = alfSize;
    vertices[23].location[Y_POS] = 0.f;
    vertices[23].location[Z_POS] = -alfSize;
    vertices[23].normal[X_POS]   = alfSize;
    vertices[23].normal[Y_POS]   = 0.f;
    vertices[23].normal[Z_POS]   = 0.f;
    vertices[23].tex[U_POS]      = alfSize;
    vertices[23].tex[V_POS]      = 0.f;

    // Index Array (define our triangles)
    triangles[0].vertexIndices[0] = 0;
    triangles[0].vertexIndices[1] = 1;
    triangles[0].vertexIndices[2] = 2;

    triangles[1].vertexIndices[0] = 2;
    triangles[1].vertexIndices[1] = 3;
    triangles[1].vertexIndices[2] = 0;

    triangles[2].vertexIndices[0] = 4;
    triangles[2].vertexIndices[1] = 5;
    triangles[2].vertexIndices[2] = 6;

    triangles[3].vertexIndices[0] = 6;
    triangles[3].vertexIndices[1] = 7;
    triangles[3].vertexIndices[2] = 4;

    triangles[4].vertexIndices[0] = 8;
    triangles[4].vertexIndices[1] = 9;
    triangles[4].vertexIndices[2] = 10;

    triangles[5].vertexIndices[0] = 10;
    triangles[5].vertexIndices[1] = 11;
    triangles[5].vertexIndices[2] = 8;

    triangles[6].vertexIndices[0] = 12;
    triangles[6].vertexIndices[1] = 13;
    triangles[6].vertexIndices[2] = 14;

    triangles[7].vertexIndices[0] = 14;
    triangles[7].vertexIndices[1] = 15;
    triangles[7].vertexIndices[2] = 12;

    triangles[8].vertexIndices[0] = 16;
    triangles[8].vertexIndices[1] = 17;
    triangles[8].vertexIndices[2] = 18;

    triangles[9].vertexIndices[0] = 18;
    triangles[9].vertexIndices[1] = 19;
    triangles[9].vertexIndices[2] = 16;

    triangles[10].vertexIndices[0] = 20;
    triangles[10].vertexIndices[1] = 21;
    triangles[10].vertexIndices[2] = 22;

    triangles[11].vertexIndices[0] = 22;
    triangles[11].vertexIndices[1] = 23;
    triangles[11].vertexIndices[2] = 20;

    // Colors
    for (int i = 0; i < 24; i++)
    {
        vertices[i].color[0] = red;
        vertices[i].color[1] = green;
        vertices[i].color[2] = blue;
        vertices[i].color[3] = alpha;
    }

    // Plane equations
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

    // Update connectivity
    unsigned int p1i, p2i, p1j, p2j;
    unsigned int i, j, ki, kj;

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

    //loadData();
}

void Mesh::draw()
{
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


// TODO:

// DRAW
//glBindBuffer(GL_ARRAY_BUFFER, vboID);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);

//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//glEnableClientState(GL_COLOR_ARRAY);
//glEnableClientState(GL_NORMAL_ARRAY);
//glEnableClientState(GL_VERTEX_ARRAY);

//glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
//glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
//glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
//glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

//glDrawElements(type, totalIndex, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));

//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//glDisableClientState(GL_COLOR_ARRAY);
//glDisableClientState(GL_NORMAL_ARRAY);
//glDisableClientState(GL_VERTEX_ARRAY);

//void Mesh::loadData()
//{
    //glGenBuffers(1, &vboID);
    //glBindBuffer(GL_ARRAY_BUFFER, vboID);

    //glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * totalVertex, NULL, GL_STATIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * totalVertex, vertices);

    //glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
    //glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
    //glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
    //glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

    //glGenBuffers(1, &indexVBOID);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);

    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * totalIndex, index, GL_STATIC_DRAW);
//}

void Mesh::drawShadow(Light *pLight, bool cap)
{
    //Vector3 p1, p2;

    //glBegin(GL_TRIANGLES);

    //// Draw the shadow volume's sides
    //for (unsigned int p = 1; p < silhouette.size(); p += 2)
    //{
        //p1 = (*silhouette[p - 1] - lightPosition) * 100000.f;
        //p2 = (*silhouette[p] - lightPosition) * 100000.f;

        //glVertex3f(silhouette[p - 1]->x, silhouette[p - 1]->y, silhouette[p - 1]->z);
        //glVertex3f(silhouette[p]->x, silhouette[p]->y, silhouette[p]->z);
        //glVertex3f(p1.x, p1.y, p1.z);

        //glVertex3f(silhouette[p]->x, silhouette[p]->y, silhouette[p]->z);
        //glVertex3f(p2.x, p2.y, p2.z);
        //glVertex3f(p1.x, p1.y, p1.z);
    //}

    //if (cap)
    //{
        //// Cap near
        //for (unsigned int t = 0; t < triangles.size(); t ++)
        //{
            //if (!triangles[t].lighted)
            //{
                //triangles[t].setCCW();
                //triangles[t].setAllVertex();
                //triangles[t].setCW();
            //}
        //}

        //// Cap far
        //for (unsigned int t = 0; t < triangles.size(); t ++)
        //{
            //if (!triangles[t].lighted)
            //{
                //triangles[t].setTransformationMIN(lightPosition);
                //triangles[t].setTransformationMUL(100000.f);
                //triangles[t].setAllVertex();
                //triangles[t].resetTransformation();
            //}
        //}
    //}

    //glEnd();
}

//void Mesh::updateConnectivity()
//{
    //vector<Point*> pointList;

    //bool found;

    //// Make a list of all unic points
    //for (unsigned int t = 0; t < triangles.size(); t ++)
    //{
        //for (unsigned int p1 = 0; p1 < 3; p1 ++)
        //{
            //found = false;
            //for (unsigned int p2 = 0; p2 < pointList.size(); p2 ++)
            //{
                //if (triangles[t].points[p1] == pointList[p2])
                //{
                    //found = true;
                    //break;
                //}
            //}
            //if (!found)
            //{
                //pointList.push_back(triangles[t].points[p1]);
            //}
        //}
    //}

    //// Complet the points sharedTriangles list
    //for (unsigned int p1 = 0; p1 < pointList.size(); p1 ++)
    //{
        //pointList[p1]->sharedTriangles.clear();

        //for (unsigned int t = 0; t < triangles.size(); t ++)
        //{
            //for (unsigned int p2 = 0; p2 < 3; p2 ++)
            //{
                //if (pointList[p1] == triangles[t].points[p2])
                //{
                    //pointList[p1]->sharedTriangles.push_back(&triangles[t]);
                //}
            //}
        //}
    //}
//}

//void Mesh::updateShadows(Vector3 lightPosition)
//{
    //silhouette.clear();

    //// Compute which triangles are casting shadows
    //for (unsigned int t = 0; t < triangles.size(); t ++)
    //{
        //triangles[t].lighted = Vector3Util::Dot(lightPosition, triangles[t].getNormal()) < 0;
    //}

    //bool silhouettePoints[3];

    //// For each triangle
    //for (unsigned int t = 0; t < triangles.size(); t ++)
    //{
        //// If it casts shadows
        //if (!triangles[t].lighted)
        //{
            //silhouettePoints[0] = false;
            //silhouettePoints[1] = false;
            //silhouettePoints[2] = false;

            //// For each one of its point
            //for (unsigned int p = 0; p < 3; p ++)
            //{
                //for (unsigned int s = 0; s < triangles[t].points[p]->sharedTriangles.size(); s ++)
                //{
                    //if (triangles[t].points[p]->sharedTriangles[s]->lighted)
                    //{
                        //silhouettePoints[p] = true;
                    //}
                //}
            //}

            //if (silhouettePoints[0] && silhouettePoints[1])
            //{
                //silhouette.push_back(triangles[t].points[0]);
                //silhouette.push_back(triangles[t].points[1]);
            //}

            //if (silhouettePoints[1] && silhouettePoints[2])
            //{
                //silhouette.push_back(triangles[t].points[1]);
                //silhouette.push_back(triangles[t].points[2]);
            //}
        //}
    //}
//}

