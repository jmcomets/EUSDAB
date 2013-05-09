#include <states/hit.h>

namespace EUSDAB
{
    namespace States
    {
        Hit::Hit():
            State()
        {
        }

        Hit::~Hit()
        {
        }

        void Hit::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Hit::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Hit::onLeft(const Event & e)
        {
            State::onLeft(e);
        
            
        }

        void Hit::onRight(const Event & e)
        {
            State::onRight(e);
            
        }

        void Hit::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
