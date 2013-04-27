#include <state.h>
#include <entity.h>
#include <stdexcept>

namespace EUSDAB
{
    State::State():
        _entity(nullptr),
        _speaker(nullptr)
    {
    }

    State::State(Entity * entity, Input::Speaker * speaker):
        _entity(entity),
        _speaker(speaker)
    {
    }

    State::~State()
    {
    }

    Entity * State::entity() const
    {
        return _entity;
    }
    
    Entity * State::entity(Entity * e)
    {
        return _entity = e;
    }

    void State::switchState(Movement const & id)
    {
        State * s = _entity->state(id);
        if (s == nullptr)
        {
            throw std::runtime_error("Undefined State");
        }
        _speaker->setListener(s);
        _entity->setState(s);
    }
}
