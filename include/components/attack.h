#ifndef ATTACK_H_
#define ATTACK_H_

#include <list>
#include <attack.h>

namespace EUSDAB
{
    namespace Components
    {
        class Attack
        {
            public:
                Attack() = default;
                Attack(Attack &&) = default;
                Attack(const Attack &) = default;
                ~Attack() = default;
                Attack & operator=(const Attack &) = default;
                template <typename Iterator>
                    void pushAttack(Iterator begin, Iterator end)
                {
                    for (; begin != end; begin++)
                    {
                        pushAttack(*begin);
                    }
                }
                void pushAttack(Attack *);

            private:
                std::list<EUSDAB::Attack *> _attacks
        };
    }
}

#endif
