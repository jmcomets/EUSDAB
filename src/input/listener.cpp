#include <input/listener.h>

namespace EUSDAB
{
    namespace Input
    {
        Listener::Listener():
            _time(0)
        {
        }

        Listener::~Listener()
        {
        }

        void Listener::onUp(const Event &)
        {
        }

        void Listener::onDown(const Event &)
        {
        }

        void Listener::onLeft(const Event &)
        {
        }

        void Listener::onRight(const Event &)
        {
        }

        void Listener::onA(const Event &)
        {
        }

        void Listener::onB(const Event &)
        {
        }

        void Listener::onX(const Event &)
        {
        }

        void Listener::onY(const Event &)
        {
        }

        void Listener::onZ(const Event &)
        {
        }

        void Listener::onTrigger(const Event &)
        {
        }

        void Listener::onNextFrame()
        {
            _time++;
        }

        void Listener::onAttack(const Event &)
        {
        }

        void Listener::onDamage(const Event &)
        {
        }

        void Listener::onEnter()
        {
            _time = 0;
        }

        void Listener::onLeave()
        {
        }

        void Listener::onCollide(Event const &)
        {
        }

        void Listener::onGrab(Event const &)
        {
        }

        void Listener::onGround(Event const &)
        {
        }
    }
}
