#ifndef DEF_OBJECTCOMPARER
#define DEF_OBJECTCOMPARER

#include "Object.h"

class ObjectComparer
{
    public:

        bool operator()(Object *o1, Object *o2) const;
};

inline bool ObjectComparer::operator() (Object *o1, Object *o2) const
{
    return (((*o1).getY() + (*o1).getY()) / 2.f) < (((*o2).getY() + (*o2).getY()) / 2.f);
}

#endif

