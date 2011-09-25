#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include <SFML/Graphics.hpp>

#define X_POS 0
#define Y_POS 1
#define Z_POS 2

#define U_POS 0
#define V_POS 1

#define R_POS 0
#define G_POS 1
#define B_POS 2
#define A_POS 3

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define TO_GRID(i) ((int)((i - 0.999999999999 + GRID_UNIT / 2.f) / GRID_UNIT))

struct Plane
{
    float a;
    float b;
    float c;
    float d;
};

struct Point3f
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct Vertex
{
    GLfloat location[3];
    GLfloat tex[2];
    GLfloat normal[3];
    GLfloat color[4];
    GLubyte padding[16];        // Pads the struct out to 64 bytes for performance increase
};

struct Triangle
{
    int vertexIndices[3];       // Index Of Each Vertex Within An Object That Makes Up The Triangle Of This Face
    Plane planeEquation;        // Equation Of A Plane That Contains This Triangle
    int neighbourIndices[3];    // Index Of Each Face That Neighbours This One Within The Object
    bool visible;               // Is The Face Visible By The Light?
};

struct Tile
{
    Tile *parent;
    bool busy;
    bool opened;
    bool closed;
    unsigned int f, g, h;
    int x, y;
};

// TODO
struct Edge
{
    int vertexIndices[2];       // Index Of Each Vertex Within the edge
    Point3f projections[2];     // Points representing each vertex projected from light's position
};

// TODO
struct Shadow
{
    Edge *pEdges;               // Will Be Dynamically Allocated
};

#endif

