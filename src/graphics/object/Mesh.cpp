#include "Mesh.h"

using namespace std;

Mesh::Mesh(Entity *e, float size, float height, float red, float green, float blue, float alpha) : Object(e)
{
    totalVertex = 24;
    totalIndex  = 36;

    float alfSize = size / 2.f;


    // FACE TOP

    vertexes[0].location[0] = -alfSize;
    vertexes[0].location[1] = height;
    vertexes[0].location[2] = -alfSize;

    vertexes[1].location[0] = alfSize;
    vertexes[1].location[1] = height;
    vertexes[1].location[2] = -alfSize;

    vertexes[2].location[0] = alfSize;
    vertexes[2].location[1] = height;
    vertexes[2].location[2] = alfSize;

    vertexes[3].location[0] = -alfSize;
    vertexes[3].location[1] = height;
    vertexes[3].location[2] = alfSize;

    index[0] = 0;
    index[1] = 1;
    index[2] = 2;
    index[3] = 2;
    index[4] = 3;
    index[5] = 0;


    // FACE FRONT LEFT

    vertexes[4].location[0] = -alfSize;
    vertexes[4].location[1] = 0.f;
    vertexes[4].location[2] = alfSize;

    vertexes[5].location[0] = -alfSize;
    vertexes[5].location[1] = height;
    vertexes[5].location[2] = alfSize;

    vertexes[6].location[0] = alfSize;
    vertexes[6].location[1] = height;
    vertexes[6].location[2] = alfSize;

    vertexes[8].location[0] = alfSize;
    vertexes[8].location[1] = 0.f;
    vertexes[8].location[2] = alfSize;

    index[6] = 4;
    index[7] = 5;
    index[8] = 6;
    index[9] = 6;
    index[10] = 7;
    index[11] = 4;


    // FACE FRONT RIGHT

    vertexes[8].location[0] = alfSize;
    vertexes[8].location[1] = 0.f;
    vertexes[8].location[2] = alfSize;

    vertexes[9].location[0] = alfSize;
    vertexes[9].location[1] = height;
    vertexes[9].location[2] = alfSize;

    vertexes[10].location[0] = alfSize;
    vertexes[10].location[1] = height;
    vertexes[10].location[2] = -alfSize;

    vertexes[11].location[0] = alfSize;
    vertexes[11].location[1] = 0.f;
    vertexes[11].location[2] = -alfSize;

    index[12] = 8;
    index[13] = 9;
    index[14] = 10;
    index[15] = 10;
    index[16] = 11;
    index[17] = 8;


    // FACE BACK LEFT

    vertexes[12].location[0] = -alfSize;
    vertexes[12].location[1] = height;
    vertexes[12].location[2] = -alfSize;

    vertexes[13].location[0] = -alfSize;
    vertexes[13].location[1] = height;
    vertexes[13].location[2] = alfSize;

    vertexes[14].location[0] = -alfSize;
    vertexes[14].location[1] = 0.f;
    vertexes[14].location[2] = alfSize;

    vertexes[15].location[0] = -alfSize;
    vertexes[15].location[1] = 0.f;
    vertexes[15].location[2] = -alfSize;

    index[18] = 12;
    index[19] = 13;
    index[20] = 14;
    index[21] = 14;
    index[22] = 15;
    index[23] = 12;


    // FACE BACK RIGHT

    vertexes[16].location[0] = alfSize;
    vertexes[16].location[1] = height;
    vertexes[16].location[2] = -alfSize;

    vertexes[17].location[0] = -alfSize;
    vertexes[17].location[1] = height;
    vertexes[17].location[2] = -alfSize;

    vertexes[18].location[0] = -alfSize;
    vertexes[18].location[1] = 0.f;
    vertexes[18].location[2] = -alfSize;

    vertexes[19].location[0] = alfSize;
    vertexes[19].location[1] = 0.f;
    vertexes[19].location[2] = -alfSize;

    index[24] = 16;
    index[25] = 17;
    index[26] = 18;
    index[27] = 18;
    index[28] = 19;
    index[29] = 16;


    // FACE B0TTOM

    vertexes[20].location[0] = -alfSize;
    vertexes[20].location[1] = 0.f;
    vertexes[20].location[2] = alfSize;

    vertexes[21].location[0] = alfSize;
    vertexes[21].location[1] = 0.f;
    vertexes[21].location[2] = alfSize;

    vertexes[22].location[0] = alfSize;
    vertexes[22].location[1] = 0.f;
    vertexes[22].location[2] = -alfSize;

    vertexes[23].location[0] = -alfSize;
    vertexes[23].location[1] = 0.f;
    vertexes[23].location[2] = -alfSize;

    index[30] = 20;
    index[31] = 21;
    index[32] = 22;
    index[33] = 22;
    index[34] = 23;
    index[35] = 20;


    // Normals
    for (int i = 0; i < 24; i+=3)
    {
        vertexes[i].normal[0]    = (vertexes[i+1].location[1] - vertexes[i].location[1]) * (vertexes[i+2].location[2] - vertexes[i].location[2]);
        vertexes[i].normal[0]   -= (vertexes[i+1].location[2] - vertexes[i].location[2]) * (vertexes[i+2].location[1] - vertexes[i].location[1]);

        vertexes[i+1].normal[1]  = (vertexes[i+1].location[2] - vertexes[i].location[2]) * (vertexes[i+2].location[0] - vertexes[i].location[0]);
        vertexes[i+1].normal[1] -= (vertexes[i+1].location[0] - vertexes[i].location[0]) * (vertexes[i+2].location[2] - vertexes[i].location[2]);

        vertexes[i+2].normal[2]  = (vertexes[i+1].location[0] - vertexes[i].location[0]) * (vertexes[i+2].location[1] - vertexes[i].location[1]);
        vertexes[i+2].normal[2] -= (vertexes[i+1].location[1] - vertexes[i].location[1]) * (vertexes[i+2].location[0] - vertexes[i].location[0]);
    }


    // Colors
    for (int i = 0; i < 24; i++)
    {
        vertexes[i].color[0] = red;
        vertexes[i].color[1] = green;
        vertexes[i].color[2] = blue;
        vertexes[i].color[3] = alpha;
    }

    // TODO fill the textures coordinates

    //loadData();
    //updateConnectivity();
}

void Mesh::draw()
{
    draw(GL_TRIANGLES);
}

void Mesh::drawOutline()
{
    draw(GL_LINE_LOOP);
}

void Mesh::draw(GLenum type)
{
    glBegin(type);
    for (unsigned int i = 0; i < totalIndex; i ++)
    {
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

