#include <states/idle.h>

namespace EUSDAB
{
    namespace States
    {
        Idle::Idle():
            State()
        {
        }

        Idle::~Idle()
        {
        }

        void Idle::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Idle::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Idle::onLeft(const Event & e)
        {
            State::onLeft(e);
        }

        void Idle::onRight(const Event & e)
        {
            State::onRight(e);
        }

        void Idle::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
