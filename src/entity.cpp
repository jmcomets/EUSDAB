#include <entity.h>
#include <stdexcept>
#include <state.h>
#include <iostream>

namespace EUSDAB
{
    Entity::Entity():
        Input::Speaker(),
        _name(),
        _physics(),
        _gravitable(true),
        _current(nullptr),
        _states(),
        _life(),
        _nbrJumpMax(2),
        _nbrJumpLeft(2),        
        _zIndex(0)
    {
    }

    Entity::~Entity()
    {
        for (auto s : _states)
        {
            delete s;
        }
    }

    void Entity::setState(State * state)
    {
        _current = state;
        setListener(state);
    }

    void Entity::setState(const Movement & mvt)
    {
        State * s = state(mvt);
        if (s == nullptr)
        {
            throw std::runtime_error("No state defined for given movement");
        }
        setState(s);
    }

    void Entity::setName(const std::string & name)
    {
        _name = name;
    }

    State * Entity::state() const
    {
        return _current;
    }

    State * Entity::state(const Movement & mvt) const
    {
        State s(mvt);
        auto it = _states.find(&s);
        return it != _states.end() ? *it : nullptr;
    }

    std::string Entity::name() const
    {
        return _name;
    }

    void Entity::addState(State * state)
    {
        if (_states.insert(state).second == false)
        {
            throw std::runtime_error("Entity's states should be unique");
        }
        state->setEntity(this);
    }

    const Physics::Vector2 & Entity::position() const
    {
        return _physics.position();
    }

    Physics::Vector2 & Entity::position()
    {
        return _physics.position();
    }

    const Physics::Transform & Entity::physics() const
    {
        return _physics;
    }

    Physics::Transform & Entity::physics()
    {
        return _physics;
    }

    void Entity::setPhysicsX(Physics::Transform const & tr)
    {
        _physics.position().x = tr.position().x;
        _physics.velocity().x = tr.velocity().x;
        _physics.acceleration().x = tr.acceleration().x;
    }

    void Entity::setPhysicsY(Physics::Transform const & tr)
    {
        _physics.position().y = tr.position().y;
        _physics.velocity().y = tr.velocity().y;
        _physics.acceleration().y = tr.acceleration().y;
    }

    bool Entity::gravitable() const
    {
        return _gravitable;
    }

    bool & Entity::gravitable()
    {
        return _gravitable;
    }

    void Entity::setLife(Life * life)
    {
        _life = life;
    }

    Life * Entity::life() const
    {
        return _life;
    }

    void Entity::setZIndex(ZIndex const & zIndex)
    {
        _zIndex = zIndex;
    }

    ZIndex const & Entity::zIndex() const
    {
        return _zIndex;
    }

    void Entity::attack(Entity * entity)
    {
        assert(entity != nullptr);
        assert(_current != nullptr);
        assert(entity->life() != nullptr);

        Attack * attack = _current->attack();

        if(attack != nullptr)
        {
           if(entity->life() == nullptr)
           {
               std::cerr << "Life is null" << std::endl;
           }
               
           entity->life()->receiveDamage(attack->damage());
           entity->_physics.velocity() = attack->direction();
        }
        else
        {
            std::cerr << "You fail to attack.. Loser." << std::endl;
        }
    }
    
    bool Entity::canJump()
    {
        return _nbrJumpLeft > 0;
    }
    
    Entity::NbJumps Entity::nbrJump()
    {
        return _nbrJumpLeft;
    }
    Entity::NbJumps Entity::nbrJumpMax()
    {
        return _nbrJumpMax;
    }
    
    void Entity::setNbrJump(Entity::NbJumps nbr)
    {
        _nbrJumpLeft = nbr;
    }
    
    bool Entity::jumpPossible()
    {
        return _jumpPossible;
    }
            
    void Entity::setJumpPossible(bool value)
    {
        _jumpPossible = value;
    }
}

