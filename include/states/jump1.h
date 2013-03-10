#ifndef JUMP1_H_
#define JUMP1_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class Jump1: public CharacterState
    {
        public:
            Jump1(Character &, DirectionX, DirectionY);
            Jump1(const Jump1 &);
            Jump1(Jump1 &&);
            virtual ~Jump1();
            Jump1 & operator=(const Jump1 &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    
        private:
            sf::Vector2f _motion;
    };
}

#endif