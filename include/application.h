#ifndef APPLICATION_H_
#define APPLICATION_H_

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
