#include <state.h>
#include <entity.h>
#include <stdexcept>
#include <iostream>

namespace EUSDAB
{
    State::State(Movement const & mvt,
            Entity * entity,
            Animation * anim,
            Graphics::SoundManager::SoundPtr soundBuffer):
        _mvt(mvt), _entity(entity),
        _animation(anim),
        _soundBuffer(soundBuffer),
        _transform(),
        //FIXME
        _attack(new Attack())
    {
        _attack->setDamage(42);
        _attack->setDirection(10, 10);
    }

    State::~State()
    {
        delete _animation;
        delete _attack;
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
        onLeave();
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

    Physics::Transform const & State::transformation() const
    {
        return _transform;
    }

    Physics::Transform & State::transformation()
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

    Graphics::SoundManager::SoundPtr State::sound() const
    {
        return _soundBuffer;
    }

    void State::setSound(Graphics::SoundManager::SoundPtr s)
    {
        _soundBuffer = s;
    }

    Attack * State::attack() const
    {
        return _attack;
    }

    void State::setAttack(Attack * attack)
    {
        _attack = attack;
    }

    void State::onNextFrame()
    {
        Listener::onNextFrame();
        _entity->_globalTime+=1;

        if (_animation != nullptr)
        {
            Animation::FrameListSize old = _animation->currentFrame();
            _animation->advance();
            if (old > _animation->currentFrame()
                    || (_animation->frame_list().size() == 1
                        && _time >= _animation->fpi()))
            {
                onAnimationEnd();
            }
        }
    }

    void State::onDamage(Event const &)
    {
        if (_mvt.flag() & Movement::Left)
        {
            switchState(Movement::OnHit | Movement::Left);
        }
        else if (_mvt.flag() & Movement::Right)
        {
            switchState(Movement::OnHit | Movement::Right);
        }
    }

    void State::onEnter()
    {
        Listener::onEnter();

        if (_soundBuffer != nullptr)
        {
            Graphics::SoundManager::playAsynchronous(_soundBuffer);
        }

        if (_animation != nullptr)
        {
            _animation->reset();
        }
        _transform = Transform();
    }

    void State::onGround(Event const & e)
    {
        Listener::onGround(e);
        _entity->setJumpPossible(true);
    }

    void State::onUp(Event const & e)
    {
        Listener::onUp(e);

        if (e.edge == Event::RisingEdge)
        {
            _entity->_verticalState = Entity::VerticalState::Up;
        }
        else if(e.edge == Event::FallingEdge)
        {
            _entity->_verticalState = Entity::VerticalState::Middle;
        }
        // std::cout << "VerticalState : " << _entity->_verticalState << std::endl;
    }

    void State::onDown(Event const & e)
    {
        Listener::onUp(e);

        if (e.edge == Event::RisingEdge)
        {
            _entity->_verticalState = Entity::VerticalState::Down;
        }
        else if(e.edge == Event::FallingEdge)
        {
            _entity->_verticalState = Entity::VerticalState::Middle;
        }
        // std::cout << "VerticalState : " << _entity->_verticalState << std::endl;
    }

    void State::onAnimationEnd()
    {
    }

    void State::onExitWorld()
    {
        // TODO
    }
}
