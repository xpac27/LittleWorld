#include "Block.h"

using namespace std;

Block::Block()
{
    parent = NULL;
    closed = false;
    opened = false;

    x = y = f = g = h = 0;
}

Block::Block(int x, int y, bool w)
{
    Block();

    this->walkable = w;
    this->x = x;
    this->y = y;
}

Vector2* Block::getPosition()
{
    return new Vector2((float)(x * 64), (float)(y * 64));
}

Block* Block::getParent()
{
    return parent;
}

void Block::setParent(Block *p)
{
    parent = p;
}

int Block::getX()
{
    return x;
}

int Block::getY()
{
    return y;
}

float Block::getXf()
{
    return (float)x;
}

float Block::getYf()
{
    return (float)y;
}

int Block::getGScore(Block *p)
{
    return p->g + ((x == p->x || y == p->y) ? 10 : 14);
}

int Block::getHScore(Block *p)
{
    return (abs(p->x - x) + abs(p->y - y)) * 10;
}

int Block::getGScore()
{
    return g;
}

int Block::getHScore()
{
    return h;
}

int Block::getFScore()
{
    return f;
}

void Block::computeScores(Block *end)
{
    g = getGScore(parent);
    h = getHScore(end);
    f = g + h;
}

bool Block::hasParent()
{
    return parent != NULL;
}

