#ifndef FALLING_H_
#define FALLING_H_

#include <characterState.h>

class Falling: public CharacterState
{
    public:
        Falling();
        Falling(const Falling &);
        Falling(Falling &&);
        virtual ~Falling();
        Falling & operator=(const Falling &);
        virtual void enter();
        virtual void leave();
        virtual void update(const sf::Input &);
};

#endif
