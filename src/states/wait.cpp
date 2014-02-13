#include <states/wait.h>

namespace EUSDAB
{
    namespace States
    {
        Wait::Wait(Movement const & m, const Movement & nextState):
            State(m), _nextState(nextState)
        {
        }

        Wait::~Wait()
        {
        }

        void Wait::onAnimationEnd()
        {
            State::onAnimationEnd();
            switchState(_nextState);
        }
    }
}
