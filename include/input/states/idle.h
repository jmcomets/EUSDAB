#ifndef IDLE_H
#define IDLE_H

#include <input/state.h>

namespace EUSDAB
{
    namespace Input
    {
        namespace States
        {
            class Idle: public State
            {
                public:
                    Idle(Idle &&) = default;
                    Idle(const Idle &) = delete;
                    Idle & operator=(const Idle &) = delete;

                    Idle();
                    virtual ~Idle() noexcept (true);

                    void onUp(Event const &);
                    void onDown(Event const &);
                    void onLeft(Event const &);
                    void onRight(Event const &);

                    //void onA(Event const &);
                    //void onB(Event const &);
                    //void onX(Event const &);
                    //void onY(Event const &);
                    //void onZ(Event const &);
                    //void onTrigger(Event const &);

                    void onNextFrame(Event const &);

                    //void onAttack(Event const &);
                    //void onDamage(Event const &);

                    //void onGround(Event const &);

                    //void onEnter();
                    //void onLeave();
            };
        }
    }
}

#endif


