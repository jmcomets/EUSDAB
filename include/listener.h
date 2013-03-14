#ifndef LISTENER_H
#define LISTENER_H

#include <ctypes>

class Speaker;

class Listener
{
    public:
        virtual void onUp(Event const &);
        virtual void onDown(Event const &);
        virtual void onLeft(Event const &);
        virtual void onRight(Event const &);

        virtual void onNextFrame(Event const &);

        virtual void onAttack(Event const &);
        virtual void onDamage(Event const &);

        virtual void onEnter();
        virtual void onLeave();

    protected:
        Speaker * _speaker;
        std::time_t _time;
};

#endif

