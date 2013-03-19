#include <input/listener.h>

namespace EUSDAB
{
    namespace Input
    {
        void Listener::onUp(const Event &) {}
        void Listener::onDown(const Event &) {}
        void Listener::onLeft(const Event &) {}
        void Listener::onRight(const Event &) {}

        void Listener::onA(const Event &) {}
        void Listener::onB(const Event &) {}
        void Listener::onX(const Event &) {}
        void Listener::onY(const Event &) {}
        void Listener::onZ(const Event &) {}
        void Listener::onTrigger(const Event &) {}

        void Listener::onNextFrame(const Event &)
        {
            _time++;
        }

        void Listener::onAttack(const Event &) {}
        void Listener::onDamage(const Event &) {}

        void Listener::onEnter()
        {
            _time = 0;
        }
        void Listener::onLeave() {}
    }
}
