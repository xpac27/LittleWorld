#include "Mesh.h"

using namespace std;

Mesh::Mesh(Entity *e, float size, float height, float red, float green, float blue, float alpha) : Object(e)
{
    totalVertex = 24;
    totalIndex  = 36;

    float alfSize = size / 2.f;

    // Top
    vertexes[0].location[X_POS]  = alfSize;  vertexes[0].location[Y_POS]  = height; vertexes[0].location[Z_POS]  = -alfSize;
    vertexes[0].normal[X_POS]    = 0.f;      vertexes[0].normal[Y_POS]    = height; vertexes[0].normal[Z_POS]    = 0.f;
    vertexes[0].tex[U_POS]       = 0.f;      vertexes[0].tex[V_POS]       = 0.f;

    vertexes[1].location[X_POS]  = -alfSize; vertexes[1].location[Y_POS]  = height; vertexes[1].location[Z_POS]  = -alfSize;
    vertexes[1].normal[X_POS]    = 0.f;      vertexes[1].normal[Y_POS]    = height; vertexes[1].normal[Z_POS]    = 0.f;
    vertexes[1].tex[U_POS]       = 0.f;      vertexes[1].tex[V_POS]       = height;

    vertexes[2].location[X_POS]  = -alfSize; vertexes[2].location[Y_POS]  = height; vertexes[2].location[Z_POS]  = alfSize;
    vertexes[2].normal[X_POS]    = 0.f;      vertexes[2].normal[Y_POS]    = height; vertexes[2].normal[Z_POS]    = 0.f;
    vertexes[2].tex[U_POS]       = alfSize;  vertexes[2].tex[V_POS]       = height;

    vertexes[3].location[X_POS]  = alfSize;  vertexes[3].location[Y_POS]  = height; vertexes[3].location[Z_POS]  = alfSize;
    vertexes[3].normal[X_POS]    = 0.f;      vertexes[3].normal[Y_POS]    = height; vertexes[3].normal[Z_POS]    = 0.f;
    vertexes[3].tex[U_POS]       = alfSize;  vertexes[3].tex[V_POS]       = 0.f;

    // Bottom
    vertexes[4].location[X_POS]  = alfSize;  vertexes[4].location[Y_POS]  = 0.f;    vertexes[4].location[Z_POS]  = alfSize;
    vertexes[4].normal[X_POS]    = 0.f;      vertexes[4].normal[Y_POS]    = 0.f;    vertexes[4].normal[Z_POS]    = 0.f;
    vertexes[4].tex[U_POS]       = 0.f;      vertexes[4].tex[V_POS]       = 0.f;

    vertexes[5].location[X_POS]  = -alfSize; vertexes[5].location[Y_POS]  = 0.f;    vertexes[5].location[Z_POS]  = alfSize;
    vertexes[5].normal[X_POS]    = 0.f;      vertexes[5].normal[Y_POS]    = 0.f;    vertexes[5].normal[Z_POS]    = 0.f;
    vertexes[5].tex[U_POS]       = 0.f;      vertexes[5].tex[V_POS]       = height;

    vertexes[6].location[X_POS]  = -alfSize; vertexes[6].location[Y_POS]  = 0.f;    vertexes[6].location[Z_POS]  = -alfSize;
    vertexes[6].normal[X_POS]    = 0.f;      vertexes[6].normal[Y_POS]    = 0.f;    vertexes[6].normal[Z_POS]    = 0.f;
    vertexes[6].tex[U_POS]       = alfSize;  vertexes[6].tex[V_POS]       = height;

    vertexes[7].location[X_POS]  = alfSize;  vertexes[7].location[Y_POS]  = 0.f;    vertexes[7].location[Z_POS]  = -alfSize;
    vertexes[7].normal[X_POS]    = 0.f;      vertexes[7].normal[Y_POS]    = 0.f;    vertexes[7].normal[Z_POS]    = 0.f;
    vertexes[7].tex[U_POS]       = alfSize;  vertexes[7].tex[V_POS]       = 0.f;

    // Front
    vertexes[8].location[X_POS]  = alfSize;  vertexes[8].location[Y_POS]  = height; vertexes[8].location[Z_POS]  = alfSize;
    vertexes[8].normal[X_POS]    = 0.f;      vertexes[8].normal[Y_POS]    = 0.f;    vertexes[8].normal[Z_POS]    = alfSize;
    vertexes[8].tex[U_POS]       = 0.f;      vertexes[8].tex[V_POS]       = 0.f;

    vertexes[9].location[X_POS]  = -alfSize; vertexes[9].location[Y_POS]  = height; vertexes[9].location[Z_POS]  = alfSize;
    vertexes[9].normal[X_POS]    = 0.f;      vertexes[9].normal[Y_POS]    = 0.f;    vertexes[9].normal[Z_POS]    = alfSize;
    vertexes[9].tex[U_POS]       = 0.f;      vertexes[9].tex[V_POS]       = height;

    vertexes[10].location[X_POS] = -alfSize; vertexes[10].location[Y_POS] = 0.f;    vertexes[10].location[Z_POS] = alfSize;
    vertexes[10].normal[X_POS]   = 0.f;      vertexes[10].normal[Y_POS]   = 0.f;    vertexes[10].normal[Z_POS]   = alfSize;
    vertexes[10].tex[U_POS]      = alfSize;  vertexes[10].tex[V_POS]      = height;

    vertexes[11].location[X_POS] = alfSize;  vertexes[11].location[Y_POS] = 0.f;    vertexes[11].location[Z_POS] = alfSize;
    vertexes[11].normal[X_POS]   = 0.f;      vertexes[11].normal[Y_POS]   = 0.f;    vertexes[11].normal[Z_POS]   = alfSize;
    vertexes[11].tex[U_POS]      = alfSize;  vertexes[11].tex[V_POS]      = 0.f;

    // Back
    vertexes[12].location[X_POS] = alfSize;  vertexes[12].location[Y_POS] = 0.f;    vertexes[12].location[Z_POS] = -alfSize;
    vertexes[12].normal[X_POS]   = 0.f;      vertexes[12].normal[Y_POS]   = 0.f;    vertexes[12].normal[Z_POS]   = -alfSize;
    vertexes[12].tex[U_POS]      = 0.f;      vertexes[12].tex[V_POS]      = 0.f;

    vertexes[13].location[X_POS] = -alfSize; vertexes[13].location[Y_POS] = 0.f;    vertexes[13].location[Z_POS] = -alfSize;
    vertexes[13].normal[X_POS]   = 0.f;      vertexes[13].normal[Y_POS]   = 0.f;    vertexes[13].normal[Z_POS]   = -alfSize;
    vertexes[13].tex[U_POS]      = 0.f;      vertexes[13].tex[V_POS]      = height;

    vertexes[14].location[X_POS] = -alfSize; vertexes[14].location[Y_POS] = height; vertexes[14].location[Z_POS] = -alfSize;
    vertexes[14].normal[X_POS]   = 0.f;      vertexes[14].normal[Y_POS]   = 0.f;    vertexes[14].normal[Z_POS]   = -alfSize;
    vertexes[14].tex[U_POS]      = alfSize;  vertexes[14].tex[V_POS]      = height;

    vertexes[15].location[X_POS] = alfSize;  vertexes[15].location[Y_POS] = height; vertexes[15].location[Z_POS] = -alfSize;
    vertexes[15].normal[X_POS]   = 0.f;      vertexes[15].normal[Y_POS]   = 0.f;    vertexes[15].normal[Z_POS]   = -alfSize;
    vertexes[15].tex[U_POS]      = alfSize;  vertexes[15].tex[V_POS]      = 0.f;

    // Left
    vertexes[16].location[X_POS] = -alfSize; vertexes[16].location[Y_POS] = height; vertexes[16].location[Z_POS] = alfSize;
    vertexes[16].normal[X_POS]   = -alfSize; vertexes[16].normal[Y_POS]   = 0.f;    vertexes[16].normal[Z_POS]   = 0.f;
    vertexes[16].tex[U_POS]      = 0.f;      vertexes[16].tex[V_POS]      = 0.f;

    vertexes[17].location[X_POS] = -alfSize; vertexes[17].location[Y_POS] = height; vertexes[17].location[Z_POS] = -alfSize;
    vertexes[17].normal[X_POS]   = -alfSize; vertexes[17].normal[Y_POS]   = 0.f;    vertexes[17].normal[Z_POS]   = 0.f;
    vertexes[17].tex[U_POS]      = 0.f;      vertexes[17].tex[V_POS]      = height;

    vertexes[18].location[X_POS] = -alfSize; vertexes[18].location[Y_POS] = 0.f;    vertexes[18].location[Z_POS] = -alfSize;
    vertexes[18].normal[X_POS]   = -alfSize; vertexes[18].normal[Y_POS]   = 0.f;    vertexes[18].normal[Z_POS]   = 0.f;
    vertexes[18].tex[U_POS]      = alfSize;  vertexes[18].tex[V_POS]      = height;

    vertexes[19].location[X_POS] = -alfSize; vertexes[19].location[Y_POS] = 0.f;    vertexes[19].location[Z_POS] = alfSize;
    vertexes[19].normal[X_POS]   = -alfSize; vertexes[19].normal[Y_POS]   = 0.f;    vertexes[19].normal[Z_POS]   = 0.f;
    vertexes[19].tex[U_POS]      = alfSize;  vertexes[19].tex[V_POS]      = 0.f;

    // Right
    vertexes[20].location[X_POS] = alfSize;  vertexes[20].location[Y_POS] = height; vertexes[20].location[Z_POS] = -alfSize;
    vertexes[20].normal[X_POS]   = alfSize;  vertexes[20].normal[Y_POS]   = 0.f;    vertexes[20].normal[Z_POS]   = 0.f;
    vertexes[20].tex[U_POS]      = 0.f;      vertexes[20].tex[V_POS]      = 0.f;

    vertexes[21].location[X_POS] = alfSize;  vertexes[21].location[Y_POS] = height; vertexes[21].location[Z_POS] = alfSize;
    vertexes[21].normal[X_POS]   = alfSize;  vertexes[21].normal[Y_POS]   = 0.f;    vertexes[21].normal[Z_POS]   = 0.f;
    vertexes[21].tex[U_POS]      = 0.f;      vertexes[21].tex[V_POS]      = height;

    vertexes[22].location[X_POS] = alfSize;  vertexes[22].location[Y_POS] = 0.f;    vertexes[22].location[Z_POS] = alfSize;
    vertexes[22].normal[X_POS]   = alfSize;  vertexes[22].normal[Y_POS]   = 0.f;    vertexes[22].normal[Z_POS]   = 0.f;
    vertexes[22].tex[U_POS]      = alfSize;  vertexes[22].tex[V_POS]      = height;

    vertexes[23].location[X_POS] = alfSize;  vertexes[23].location[Y_POS] = 0.f;    vertexes[23].location[Z_POS] = -alfSize;
    vertexes[23].normal[X_POS]   = alfSize;  vertexes[23].normal[Y_POS]   = 0.f;    vertexes[23].normal[Z_POS]   = 0.f;
    vertexes[23].tex[U_POS]      = alfSize;  vertexes[23].tex[V_POS]      = 0.f;

    // Index Array (define our triangles)
    index[0] = 0;   index[1] = 1;   index[2] = 2;
    index[3] = 2;   index[4] = 3;   index[5] = 0;

    index[6] = 4;   index[7] = 5;   index[8] = 6;
    index[9] = 6;   index[10] = 7;  index[11] = 4;

    index[12] = 8;  index[13] = 9;  index[14] = 10;
    index[15] = 10; index[16] = 11; index[17] = 8;

    index[18] = 12; index[19] = 13; index[20] = 14;
    index[21] = 14; index[22] = 15; index[23] = 12;

    index[24] = 16; index[25] = 17; index[26] = 18;
    index[27] = 18; index[28] = 19; index[29] = 16;

    index[30] = 20; index[31] = 21; index[32] = 22;
    index[33] = 22; index[34] = 23; index[35] = 20;

    // Colors
    for (int i = 0; i < 24; i++)
    {
        vertexes[i].color[0] = red;
        vertexes[i].color[1] = green;
        vertexes[i].color[2] = blue;
        vertexes[i].color[3] = alpha;
    }

    //loadData();
    //updateConnectivity();
}

void Mesh::draw()
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

void Mesh::drawOutline()
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
    //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * totalVertex, vertexes);

    //glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
    //glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
    //glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
    //glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

    //glGenBuffers(1, &indexVBOID);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);

    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * totalIndex, index, GL_STATIC_DRAW);
//}

//void Mesh::drawShadow(Vector3 lightPosition, bool cap)
//{
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
//}

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

