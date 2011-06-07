#ifndef BLOCK
#define BLOCK

#include "../graphics/Vector2.h"

#include <cstdlib>
#include <iostream>


class Block
{
    public:

        Block();
        Block(int x, int y, bool w);

        Vector2* getPosition();
        Block* getParent();

        void setParent(Block *p);
        void computeScores(Block *end);

        int getX();
        int getY();
        int getGScore(Block *p);
        int getHScore(Block *p);
        int getGScore();
        int getHScore();
        int getFScore();

        float getXf();
        float getYf();

        bool hasParent();

        bool walkable;
        bool closed;
        bool opened;


    private :

        int x;
        int y;

        unsigned int f;
        unsigned int g;
        unsigned int h;

        Block *parent;
};

#endif

