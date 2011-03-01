#ifndef DEF_DYNAMICOBJECT
#define DEF_DYNAMICOBJECT

#include <iostream>
#include "../Object.h"

class DynamicObject : public Object
{
    public:

        DynamicObject();
        virtual void update(float time);
        virtual void remove();


    protected:

        float speed;
};

#endif

