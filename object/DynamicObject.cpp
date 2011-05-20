#include "DynamicObject.h"

using namespace std;

DynamicObject::DynamicObject(World *W, float h, bool s) : Object(W, h, s)
{
    canMove = false;
}

void DynamicObject::init(Pathfinder *p)
{
    pathfinder = p;
}

void DynamicObject::update(float time)
{
}

void DynamicObject::remove()
{
}

void DynamicObject::move(float time)
{
    if (canMove == true)
    {
        if (Vector2::distance(position, destination) > 5.f)
        {
            position.x += direction.x * speed * time;
            position.y += direction.y * speed * time;
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

void DynamicObject::resetDestination()
{
    destination = position;
}

void DynamicObject::setDestination(Vector2 *d)
{
    destination.x = d->x;
    destination.y = d->y;
    direction -= destination;
    Vector2::normalize(direction);
    canMove = true;
}

void DynamicObject::setPath(Vector2 *destination)
{
    resetDestination();
    path = pathfinder->getPath(&position, destination, getSize());
    canMove = true;
}

bool DynamicObject::isCanMove()
{
    return canMove;
}

