#include <attack.h>

namespace EUSDAB {
    
    Attack::Attack(): _direction(), _damage(0)
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
}

