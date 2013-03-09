#ifndef EJECTED_H_
#define EJECTED_H_

#include <characterState.h>

class Ejected: public CharacterState
{
    public:
        Ejected();
        Ejected(const Ejected &);
        Ejected(Ejected &&);
        virtual ~Ejected();
        Ejected & operator=(const Ejected &);
        virtual void enter();
        virtual void leave();
        virtual void update(const sf::Input &);
};

#endif
