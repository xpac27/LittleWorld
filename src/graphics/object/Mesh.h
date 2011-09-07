#ifndef DEF_MESH
#define DEF_MESH

#define X_POS 0
#define Y_POS 1
#define Z_POS 2

#define U_POS 0
#define V_POS 1

#define R_POS 0
#define G_POS 1
#define B_POS 2
#define A_POS 3

#include "../Object.h"
//#include "../../math/Vector3.h"

#include <iostream>
#include <SFML/Graphics.hpp>

//#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#ifndef DEF_VERTEX
#define DEF_VERTEX
typedef struct
{
        GLfloat location[3];
        GLfloat tex[2];
        GLfloat normal[3];
        GLfloat color[4];
        GLubyte padding[16]; // Pads the struct out to 64 bytes for performance increase
} Vertex;
#endif

// TODO Have an instance of obj instead of the struct and the long constructor

class Mesh : public Object
{
    public:

        Mesh(Entity *e, float size, float height, float red, float green, float blue, float alpha);

        virtual void draw();
        virtual void outline();
        //void drawShadow(Vector3 lightPosition, bool cap);
        //void updateShadows(Vector3 lightPosition);
        //void updateConnectivity();

    private:

        //void loadData();

        unsigned int totalVertex;
        unsigned int totalIndex;

        Vertex vertexes[24];
        int index[36];

        //GLuint vboID;
        //GLuint indexVBOID;
};

#endif

