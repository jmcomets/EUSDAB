#ifndef ATTACk_H_
#define ATTACk_H_

#include <entity.h>
#include <life.h>

namespace EUSDAB
{
    class Attack
    {
        public:
            Attack(Attack &&) = default;
            Attack(Attack const &) = delete;
            Attack & operator=(Attack const &) = delete;

            Attack();
            virtual ~Attack();

            virtual void onAttack(Entity * entity) = 0;
            void setDirection(float x, float y);
            void setDamage(Life::Amount const & amount);

        private:
            Physics::Vector2T<float> _direction;
            Life::Amount _damage;
    };
}

#endif //ATTACK_H_
