#include <state.h>
#include <entity.h>
#include <stdexcept>

namespace EUSDAB
{
    State::State(Entity * entity, Input::Speaker * speaker,
            const Movement & mvt):
        _entity(entity),
        _speaker(speaker),
        _mvt(mvt), _hitboxList()
    {
    }

    State::~State()
    {
    }

    Entity * State::entity() const
    {
        return _entity;
    }
    
    void State::setEntity(Entity * e)
    {
        _entity = e;
    }

    State::Speaker * State::speaker() const
    {
        return _speaker;
    }
    
    void State::setSpeaker(State::Speaker * s)
    {
        _speaker = s;
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

    const State::HitboxList & State::hitboxList() const
    {
        return _hitboxList;
    }
}
