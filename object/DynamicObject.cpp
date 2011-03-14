#include "DynamicObject.h"

using namespace std;

DynamicObject::DynamicObject(World *w, float h) : Object(w, h)
{
    canMove = false;
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
        if (position.getDistanceTo(&destination) > 5.f)
        {
            position.x += direction.getX() * speed * time;
            position.y += direction.getY() * speed * time;
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

void DynamicObject::setDestination(Position *p)
{
    cout << "GOTO: " << p->x << "x" << p->y << endl;
    setDestination(p->x, p->y);
}
void DynamicObject::setDestination(float x, float y)
{
    destination.set(x, y);
    direction.set(&position, &destination);
    canMove = true;
}

void DynamicObject::setPath(vector<Position*> p)
{
    resetDestination();
    path = p;
    canMove = true;
}

