#ifndef JUMP_H_
#define JUMP_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class Jump: public BaseState
    {
        public:
            Jump(Character &, DirectionX, DirectionY, unsigned int jumpNbr, unsigned int jumpNbrMax );
            Jump(const Jump &);
            Jump(Jump &&);
            virtual ~Jump();
            Jump & operator=(const Jump &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    
        private:
            sf::Vector2f _motion;
            unsigned int jumpNumber;
            unsigned int jumpNumberMax;
            unsigned int frameCounter;
    };
}

#endif
