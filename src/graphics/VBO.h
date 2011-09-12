#ifndef DEF_VBO
#define DEF_VBO

#include "../resources/Structs.h"
#include "../resources/Conf.h"

#include <iostream>

class VBO
{
    public:

        VBO(unsigned int tv, unsigned int ti);

        void uploadVertices(Vertex *vertices, GLubyte *indexes);
        void draw();


    private:

        unsigned int totalVertex;
        unsigned int totalIndexes;

        GLuint vboID;
        GLuint indexVBOID;
};

#endif

