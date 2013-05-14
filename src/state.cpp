#include <state.h>
#include <entity.h>
#include <stdexcept>

namespace EUSDAB
{
    State::State(const Movement & mvt, 
            Entity * entity, Animation * anim):
        _mvt(mvt), _entity(entity),
        _animation(anim),
        _transform()
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
        s->onEnter();
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

    Physics::Transform const & State::transformation() const
    {
        return _transform;
    }

    void State::setTransformation(Physics::Transform const & tr)
    {
        _transform = tr;
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
            Animation::FrameListSize old = _animation->currentFrame();
            _animation->advance();
            if (old > _animation->currentFrame())
            {
                onAnimationEnd();
            }
        }
    }
    
    void State::onEnter()
    {
        if (_animation != nullptr)
        {
            _animation->reset();
        }
    }

    void State::onAnimationEnd()
    {
    }

    void State::onExitWorld()
    {
        // TODO
    }
}
