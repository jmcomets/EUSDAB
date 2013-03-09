#ifndef SPECIAL_H_
#define SPECIAL_H_

#include <characterState.h>

class Special: public CharacterState
{
    public:
        Special(Character &);
        Special(const Special &);
        Special(Special &&);
        virtual ~Special();
        Special & operator=(const Special &);
        virtual void enter();
        virtual void leave();
        virtual void update();
};

#endif
