#ifndef INPUT_LISTENER_H_
#define INPUT_LISTENER_H_

#include <ctypes>
#include <input/speaker.h>

namespace EUSDAB
{
    namespace Input
    {
        class Listener
        {
            public:
                virtual void onUp(Event const &);
                virtual void onDown(Event const &);
                virtual void onLeft(Event const &);
                virtual void onRight(Event const &);

                virtual void onA(Event const &);
                virtual void onB(Event const &);
                virtual void onX(Event const &);
                virtual void onY(Event const &);
                virtual void onZ(Event const &);
                virtual void onTrigger(Event const &);

                virtual void onNextFrame(Event const &);

                virtual void onAttack(Event const &);
                virtual void onDamage(Event const &);

                virtual void onEnter();
                virtual void onLeave();

            protected:
                std::time_t _time;
        };
    }
}

#endif
