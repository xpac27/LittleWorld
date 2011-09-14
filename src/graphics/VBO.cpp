#include "VBO.h"

using namespace std;

VBO::VBO(unsigned int tv, unsigned int ti)
{
    totalVertex = tv;
    totalIndexes = ti;
}

void VBO::uploadVertices(Vertex *vertices, GLubyte *indexes)
{
    // CAN BE WIDLY OPTIMIZED BY CREATING A SINGLE BUFFER FOR THE WHOLE GAME
    // AND BINDING IT JUST ONCE TO DRAW VERTEXES SEGEMENT BY SEGMENT ACCORDING
    // TO EACH REGISTERED OBJECT

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * totalVertex, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * totalVertex, vertices);

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

    //glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
    glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

    glDrawElements(GL_TRIANGLES, totalIndexes, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
}

