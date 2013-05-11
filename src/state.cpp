#include <state.h>
#include <entity.h>
#include <stdexcept>
#include <string>

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
            std::string msg("Undefined State");
#ifdef DEBUG
            msg += " of movement ";
            msg += mvt.debug();
            msg += " current state movement is ";
            msg += _entity->state()->movement().debug();
#endif
            throw std::runtime_error(msg);
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
        _animation->reset();
    }

    void State::onAnimationEnd()
    {
    }
}
