#ifndef INPUT_LISTENER_H_
#define INPUT_LISTENER_H_

#include <ctime>

namespace EUSDAB
{
    namespace Input
    {
        class Event;

        class Listener
        {
            public:
                Listener(Listener &&) = default;
                Listener(const Listener &) = default;
                Listener & operator=(const Listener &) = default;

                Listener();
                virtual ~Listener();

                // Direction events
                virtual void onUp(Event const &);
                virtual void onDown(Event const &);
                virtual void onLeft(Event const &);
                virtual void onRight(Event const &);

                // Action events
                virtual void onA(Event const &);
                virtual void onB(Event const &);
                virtual void onX(Event const &);
                virtual void onY(Event const &);
                virtual void onZ(Event const &);
                virtual void onTrigger(Event const &);

                // Next frame event
                virtual void onNextFrame();

                // Attack events
                virtual void onAttack(Event const &);
                virtual void onDamage(Event const &);

                // Collision event
                virtual void onCollide(Event const &);

                // Grab/Ground events
                virtual void onGrab(Event const &);
                virtual void onGround(Event const &);

                // Enter/Leave state events
                virtual void onEnter();
                virtual void onLeave();

            protected:
                std::time_t _time;
        };
    }
}

#endif
