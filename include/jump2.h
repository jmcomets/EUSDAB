#ifndef JUMP2_H_
#define JUMP2_H_

#include <characterState.h>

class Jump2: public CharacterState
{
    public:
        Jump2();
        Jump2(const Jump2 &);
        Jump2(Jump2 &&);
        virtual ~Jump2();
        Jump2 & operator=(const Jump2 &);
        virtual void enter();
        virtual void leave();
        virtual void update(const sf::Input &);
};

#endif
