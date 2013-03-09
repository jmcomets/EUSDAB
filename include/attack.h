#ifndef ATTACK_H_
#define ATTACK_H_

#include <characterState.h>
#include <character.h>

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
        virtual void update(const JoystickState &);
	private:
		unsigned int countdown;
};

#endif
