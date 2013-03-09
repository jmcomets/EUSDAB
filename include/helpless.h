#ifndef HELPLESS_H_
#define HELPLESS_H_

#include <characterState.h>

class Helpless: public CharacterState
{
    public:
        Helpless(Character &);
        Helpless(const Helpless &);
        Helpless(Helpless &&);
        virtual ~Helpless();
        Helpless & operator=(const Helpless &);
        virtual void enter();
        virtual void leave();
        virtual void update(const JoystickState update());
};

#endif
