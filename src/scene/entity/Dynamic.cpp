#include "Dynamic.h"

using namespace std;

Dynamic::Dynamic(World *W, float s) : Entity(W, s)
{
    canMove = false;
}

void Dynamic::update(float time)
{
}

void Dynamic::onNotify(unsigned const int type)
{
}

void Dynamic::move(float time)
{
    if (canMove == true)
    {
        if (Vector3Util::dist(position, destination) > 5.f)
        {
            position += direction * speed * time;
        }
        else if (path.size() > 0)
        {
            setDestination(path.back());
            path.pop_back();
        }
        else
        {
            canMove = false;
        }
    }
}

void Dynamic::resetDestination()
{
    destination = position;
}

void Dynamic::setDestination(Vector3 *d)
{
    destination = *d;
    direction = destination - position;
    Vector3Util::Normalize(direction);
    canMove = true;
}

void Dynamic::setPath(float x, float z)
{
    resetDestination();
    // TODO:
    //path = pathfinder->getPath(position.x, position.z, x, z, getSize());
    path.clear();
    path.push_back(new Vector3(x, 0.f, z));
    canMove = true;
}

bool Dynamic::isCanMove()
{
    return canMove;
}

