#ifndef ATTACK_H_
#define ATTACK_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class Attack: public CharacterState
    {
        public:
            Attack(Character &, DirectionX, DirectionY, const unsigned int);
            Attack(const Attack &);
            Attack(Attack &&);
            virtual ~Attack();
            Attack & operator=(const Attack &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    
        private:
            unsigned int countdown;
    };
}

#endif
