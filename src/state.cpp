#include <state.h>
#include <entity.h>
#include <stdexcept>

namespace EUSDAB
{
    State::State(Entity * entity, Input::Speaker * speaker,
            const Movement & mvt):
        _mvt(mvt),
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

    Movement State::movement() const
    {
        return _mvt;
    }

    void State::setMovement(const Movement & mvt)
    {
        _mvt = mvt;
    }
}
