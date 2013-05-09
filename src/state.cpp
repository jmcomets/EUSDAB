#include <state.h>
#include <entity.h>
#include <stdexcept>
#include <iostream>

namespace EUSDAB
{
    State::State(const Movement & mvt, 
            Entity * entity, Animation * anim):
        _mvt(mvt), _entity(entity),
        _animation(anim)
    {
    }

    State::~State()
    {
        delete _animation;
    }

    Entity * State::entity() const
    {
        return _entity;
    }
    
    void State::setEntity(Entity * e)
    {
        _entity = e;
    }

    void State::switchState(const Movement & mvt)
    {
        State * s = _entity->state(mvt);
        if (s == nullptr)
        {
            throw std::runtime_error("Undefined State");
        }
        _entity->setState(s);
    }
    
    void State::switchState(Movement::Flag const & f)
    {
        switchState(Movement(f));
    }

    Movement State::movement() const
    {
        return _mvt;
    }

    void State::setMovement(const Movement & mvt)
    {
        _mvt = mvt;
    }

    bool State::operator<(const State & st) const
    {
        return _mvt < st._mvt;
    }

    Animation * State::animation() const
    {
        return _animation;
    }

    void State::setAnimation(Animation * a)
    {
        _animation = a;
    }

    void State::onNextFrame()
    {
        Listener::onNextFrame();
        if (_animation != nullptr)
        {
            _animation->advance();
        }
    }
}
