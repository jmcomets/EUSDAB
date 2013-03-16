#include <input/state.h>
#include <entity.h>

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
