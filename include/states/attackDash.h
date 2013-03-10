#ifndef ATTACK_DASH_H_
#define ATTACK_DASH_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class AttackDash: public CharacterState
    {
        public:
            AttackDash(Character &);
            AttackDash(const AttackDash &);
            AttackDash(AttackDash &&);
            virtual ~AttackDash();
            AttackDash & operator=(const AttackDash &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    };
}

#endif