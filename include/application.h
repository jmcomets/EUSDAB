#ifndef __APPLICATION_H__
#define __APPLICATION_H__

class Application
{
    public:
        explicit Application();

        virtual ~Application();

        void run();

    protected:
        virtual void event();
        virtual void update();
        virtual void render();
};

#endif

