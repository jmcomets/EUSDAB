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

            void setDirection(Physics::Vector2 direction);
            void setDirection(const Physics::Unit & x,
                    const Physics::Unit & y);
            Physics::Vector2 const & direction();
            void setDamage(Life::Amount const & amount);
            Life::Amount const & damage();
            bool applyTo(Entity * entity);
            void reset();



        private:
            Physics::Vector2 _direction;
            Life::Amount _damage;
            std::set<Entity *> _entityMasks;
    };
}

#endif //ATTACK_H_
