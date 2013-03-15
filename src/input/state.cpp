#include <input/state.h>

namespace EUSDAB
{
    namespace Input
    {
        State::State(Entity * entity, Speaker * speaker):
            _entity(entity),
            _speaker(speaker)
        {
        }

        State::~State()
        {
        }
    }
}
