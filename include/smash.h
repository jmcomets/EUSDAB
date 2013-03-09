#ifndef SMASH_H_
#define SMASH_H_

#include <characterState.h>
#include <character.h>

class Smash: public CharacterState
{
    public:
        Smash(Character &, DirectionX, DirectionY, const unsigned int);
        Smash(const Smash &);
        Smash(Smash &&);
        virtual ~Smash();
        Smash & operator=(const Smash &);
        virtual void enter();
        virtual void leave();
        virtual void update(const JoystickState &);
	private:
		unsigned int countdown;
};

#endif
