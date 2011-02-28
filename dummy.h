#ifndef DEF_DUMMY
#define DEF_DUMMY

class Dummy
{
    public:

        Dummy();
        void draw();
        void update(double time);


    private:

        double x;
        double y;
        double speed;
};

#endif

