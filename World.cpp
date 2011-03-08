#include "World.h"

using namespace std;

World::World()
{
}

void World::draw()
{
    list<StaticObject*>::iterator Si;
    for (Si = staticObjectList.begin(); Si != staticObjectList.end(); ++ Si)
    {
        camera.draw(*Si);
    }

    list<DynamicObject*>::iterator Di;
    for (Di = dynamicObjectList.begin(); Di != dynamicObjectList.end(); ++ Di)
    {
        camera.draw(*Di);
    }
}

void World::update(float time)
{
    list<DynamicObject*>::iterator i;
    for (i = dynamicObjectList.begin(); i != dynamicObjectList.end(); ++ i)
    {
        (*i)->update(time);
    }

    camera.update(time);

    if (mouseX > 0 && mouseX < 10000 && mouseY > 0 && mouseY < 1000)
    {
        vector<StaticObject*> objects = getTraversingStaticObjects(new Position(256.f, 256.f), new Position((float)mouseX, (float)mouseY));

        for (unsigned int i = 0; i < objects.size(); i++)
        {
            objects[i]->touched = true;
        }
    }
    //getTraversingStaticObjects(new Position(2.2f * 64.f, 3.1f * 64.f), new Position(5.7f * 64.f, 4.1f * 64.f));
}

void World::addDynamicObject(DynamicObject *o)
{
    o->init();
    dynamicObjectList.push_back(o);
}

void World::addStaticObject(StaticObject *o)
{
    o->init();
    staticObjectList.push_back(o);
    staticObjectMap[o->getGridX()][o->getGridY()].push_back(o);

    cout << o->getGridX() << " x " << o->getGridY() << endl;
}

void World::setFocus(Object *o)
{
    camera.setFocus(o);
}

void World::updateMousePosition(float mouseScreenX, float mouseScreenY)
{
    // Origin is on the screen so correct position
    mouseScreenX -= 400.f;
    mouseScreenY -= 300.f;

    // Apply transformation
    mouseX = (mouseScreenX + (mouseScreenY * 2.f)) / 2.f;
    mouseY = ((mouseScreenY * 2.f) - mouseScreenX) / 2.f;

    // Add camera offset
    mouseX += camera.getX();
    mouseY += camera.getY();

    // Corect cursor
    mouseX += 16.f;
    mouseY += 8.f;
}

vector<StaticObject*> World::getTraversingStaticObjects(Position *from, Position *to)
//void World::getTraversingStaticObjects(Position *from, Position *to)
{
    vector<StaticObject*> objects;

    //Calculate m and b for the line equation:
    float m = ((to->y / 64.f) - (from->y / 64.f)) / ((to->x / 64.f) - (from->x / 64.f));
    float b = ((from->y + 32.f) / 64.f) - (m * ((from->x + 32.f) / 64.f));

    // Define vars (c=current, n=next, d=direction, e=end)
    float cx = (float)from->getGridX();
    float cy = (float)from->getGridY();
    float ex = (float)to->getGridX();
    float ey = (float)to->getGridY();
    float dx = (cx < ex) ? 1.f : -1.f;
    float dy = (cy < ey) ? 1.f : -1.f;
    float nx, ny;

    unsigned int i = 0;
    unsigned int n = 0;

    cout << "=============" << endl;
    cout << cx << "x" << cy << " to " << ex << "x" << ey << endl;
    //cout << "m: " << m << " - b: " << b << endl;
    //cout << "dx: " << dx << " - dy: " << dy << endl;
    //cout << "ex: " << ex << " - ey: " << ey << endl;
    cout << "-------------" << endl;

    for (i = 0; i < staticObjectMap[cx][cy].size(); i ++)
    {
        objects.push_back(staticObjectMap[cx][cy][i]);
    }

    // While we do not reach the end position
    while ((cx != ex || cy != ey) && n < 10)
    {
        // Move 1 tile on x and on y
        nx = cx + dx;
        ny = cy + dy;

        // Compare next y value on the x abscissa (x=(y-b)/m) to the curent
        // if it's the value of the adjacent tile use it
        //cout << "ny: " << ny << endl;
        //cout << abs(((ny - b) / m) - cx)  << " then " << ny << endl;
        //cout << "cy >> " << abs(((ny - b) / m) - cx) << endl;
        //cy = (abs(((ny - b) / m) - cx) <= 1.f) ? ny : cy;

        // Do the same for the next x value (y=m*x+b)
        //cout << "nx: " << nx << endl;
        //cout << abs(((m * nx) + b) - cy)  << " then " << nx << endl;
        //cout << "cx >> " << abs(((m * nx) + b) - cy) << endl;
        //cx = (abs(((m * nx) + b) - cy) <= 1.f) ? nx : cx;

        //if(abs(((ny - b) / m) - cx) <= max)
        //if(abs(((ny - b) / m) - cx) <= abs(((m * nx) + b) - cy))
        cout << abs(((ny - b) / m) - cx) << " < " << abs(((m * nx) + b) - cy) << endl;
        //if(abs(((ny - b) / m) - cx) < abs(((m * nx) + b) - cy))
        if(abs(((ny - b) / m) - cx) <= 2.f)
        {
            if (ny > ey && cx < ex) {
              cx = nx;
              cout << "- 1" << endl;
            } else {
              cy = ny;
              cout << "- 2" << endl;
            }
        }
        else
        {
            if (nx > ex && cy < ey) {
              cy = ny;
              cout << "- 3" << endl;
            } else {
              cx = nx;
              cout << "- 4" << endl;
            }
        }

        //cout << cx << " x " << cy << endl;

        // Add all the objects in this tile to the list
        for (i = 0; i < staticObjectMap[cx][cy].size(); i ++)
        {
            objects.push_back(staticObjectMap[cx][cy][i]);
        }

        cout << " " << endl;

        n ++;
    }

    cout << " " << endl;

    return objects;
}

