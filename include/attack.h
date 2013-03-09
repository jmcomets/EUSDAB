#ifndef ATTACK_H_
#define ATTACK_H_

#include <characterState.h>

class Attack: public CharacterState
{
    public:
        Attack(Character &);
        Attack(const Attack &);
        Attack(Attack &&);
        virtual ~Attack();
        Attack & operator=(const Attack &);
        virtual void enter();
        virtual void leave();
        virtual void update();
};

#endif
