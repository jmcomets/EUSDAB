#include <input/state.h>
#include <entity.h>

namespace EUSDAB
{
    namespace Input
    {
        State::State():
            _entity(nullptr),
            _speaker(nullptr)
        {
        }

        State::State(Entity * entity, Speaker * speaker):
            _entity(entity),
            _speaker(speaker)
        {
        }

        State::~State()
        {
        }
        
        void State::entity(Entity * e)
        {
            _entity = e;
        }
    }
}
