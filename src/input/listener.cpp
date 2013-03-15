#include <input/listener.h>

namespace EUSDAB
{
    namespace Input
    {
        void Listener::onUp(Event const &) {}
        void Listener::onDown(Event const &) {}
        void Listener::onLeft(Event const &) {}
        void Listener::onRight(Event const &) {}

        void Listener::onA(Event const &) {}
        void Listener::onB(Event const &) {}
        void Listener::onX(Event const &) {}
        void Listener::onY(Event const &) {}
        void Listener::onZ(Event const &) {}
        void Listener::onTrigger(Event const &) {}

        void Listener::onNextFrame(Event const &)
        {
            _time++;
        }

        void Listener::onAttack(Event const &) {}
        void Listener::onDamage(Event const &) {}

        void Listener::onEnter()
        {
            _time = 0;
        }
        void Listener::onLeave() {}
    }
}

