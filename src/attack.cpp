#include <attack.h>

namespace EUSDAB {
    
    Attack::Attack(): _direction(), _damage()
    {
    }    

    Attack::~Attack()
    {
    }

    void Attack::setDirection(float x, float y)
    {
        _direction.x = x;
        _direction.y = y;
    }

    void Attack::setDamage(Life::Amount const & amount)
    {
        _damage = amount;
    }
}

