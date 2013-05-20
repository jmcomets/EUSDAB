#include <attack.h>

namespace EUSDAB {
    
    Attack::Attack(): _direction(), _damage(0), _entityMasks()
    {
    }    

    Attack::~Attack()
    {
    }

    void Attack::setDirection(const Physics::Unit & x,
            const Physics::Unit & y)
    {
        _direction.x = x;
        _direction.y = y;
    }

    void Attack::setDirection(Physics::Vector2 direction)
    {
        _direction = direction;
    }

    Physics::Vector2 const & Attack::direction()
    {
        return _direction;
    }

    void Attack::setDamage(Life::Amount const & amount)
    {
        _damage = amount;
    }

    Life::Amount const & Attack::damage()
    {
        return _damage;
    }

    bool Attack::applyTo(Entity * entity)
    {
        std::pair<std::set<Entity *>::iterator, bool> 
            inserted_pair = _entityMasks.insert(entity);

        if(inserted_pair.second == true)
        {
            entity->life()->receiveDamage(_damage);
            entity->physics().velocity() = _direction;
            return true;
        }
        return false;
    }

    void Attack::reset()
    {
        _entityMasks.clear();
    }

}

