#ifndef ATTACK_H_
#define ATTACK_H_

#include <entity.h>
#include <life.h>

namespace EUSDAB
{
    class Entity;
    class Attack
    {
        public:
            Attack(Attack &&) = default;
            Attack(Attack const &) = delete;
            Attack & operator=(Attack const &) = delete;

            Attack();
            virtual ~Attack();

            void setDirection(float x, float y);
            Physics::Vector2 const & direction();
            void setDamage(Life::Amount const & amount);
            Life::Amount const & damage();

        private:
            Physics::Vector2 _direction;
            Life::Amount _damage;
    };
}

#endif //ATTACK_H_
