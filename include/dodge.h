#ifndef DODGE_H_
#define DODGE_H_

#include <characterState.h>

class Dodge: public CharacterState
{
    public:
        Dodge();
        Dodge(const Dodge &);
        Dodge(Dodge &&);
        virtual ~Dodge();
        Dodge & operator=(const Dodge &);
        virtual void enter();
        virtual void leave();
        virtual void update(const sf::Input &);
};

#endif
