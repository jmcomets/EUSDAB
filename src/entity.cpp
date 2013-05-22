#include <entity.h>
#include <stdexcept>
#include <state.h>
#include <iostream>

namespace EUSDAB
{
    Entity::Entity():
        Input::Speaker(),
        _name(),
        _physics(), _gravitable(true),
        _current(nullptr), _states(),
        _life(nullptr),
        _zIndex(0),
        _nbrJumpLeft(2), _nbrJumpMax(2), //FIXME
        _jumpPossible(true),
        _hb_collision(Physics::Hitbox::Collision),
        _verticalState(VerticalState::Middle),
        _globalTime(0),
        _shieldValue(1000),
        _shieldMaxValue(1000),
        _shieldLeaveTime(0),
        _attackable(true)
    {
    }

    Entity::~Entity()
    {
        for (auto s : _states)
        {
            delete s;
        }
        delete _life;
    }

    Physics::Hitbox const & Entity::hitbox() const
    {
        return _hb_collision;
    }

    Physics::Hitbox & Entity::hitbox()
    {
        return _hb_collision;
    }

    std::set<State *, std::less_ptr<State>> const & Entity::states() const
    {
        return _states;
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
        for(auto it : _states)
        {
            //std::cout << "State of movement : " << it->movement().debug() << std::endl;
        }
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
        std::cout << "###State of movement : " << state->movement().debug() << std::endl;
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

    void Entity::setGravitable(bool gravitable)
    {
        _gravitable = gravitable;
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

    void Entity::setAttackable(bool a)
    {
        _attackable = a;
    }

    bool Entity::attackable() const
    {
        return _attackable;
    }

    void Entity::attack(Entity * entity)
    {
        assert(entity != nullptr);
        assert(_current != nullptr);
        assert(entity->life() != nullptr);
        assert(entity != this);

        Attack * attack = _current->attack();

        if(!entity->attackable())
            return;

        if(attack != nullptr)
        {
            attack->applyTo(entity);
            std::cout << "<Attack> " << _name << " : " << _physics << std::endl;
            std::cout << "<Attack> " << entity->_name << " : " << entity->_physics << std::endl;
        }
        else
        {
            std::cerr << "You fail to attack.. Loser." << std::endl;
        }
    }

    bool Entity::canJump()
    {
        std::cout << "jumpLeft : " << _nbrJumpLeft << std::endl;
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

