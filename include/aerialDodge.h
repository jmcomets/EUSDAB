#ifndef AERIAL_DODGE_H_
#define AERIAL_DODGE_H_

#include <characterState.h>

class AerialDodge: public CharacterState
{
    public:
        AerialDodge();
        AerialDodge(const AerialDodge &);
        AerialDodge(AerialDodge &&);
        virtual ~AerialDodge();
        AerialDodge & operator=(const AerialDodge &);
        virtual void enter();
        virtual void leave();
        virtual void update(const sf::Input &);
};

#endif
