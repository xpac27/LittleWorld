#ifndef DEF_OBJECT
#define DEF_OBJECT

class Object
{
    public:

        Object();
        virtual void init();
        virtual void draw();


    protected:

        float x;
        float y;
        float size;
};

#endif

