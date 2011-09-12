#include "VBO.h"

using namespace std;

VBO::VBO(unsigned int tv, unsigned int ti)
{
    totalVertex = tv;
    totalIndexes = ti;
}

void VBO::uploadVertices(Vertex *vertices, GLubyte *indexes)
{
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * totalVertex, vertices, GL_STATIC_DRAW);

    //glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
    glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

    glGenBuffers(1, &indexVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * totalIndexes, indexes, GL_STATIC_DRAW);
}

void VBO::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);

    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    //glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
    glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

    glDrawElements(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));

    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

