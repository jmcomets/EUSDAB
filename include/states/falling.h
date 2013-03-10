#ifndef FALLING_H_
#define FALLING_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class Falling: public BaseState
    {
        public:
            Falling(Character &, DirectionX, DirectionY);
            Falling(const Falling &);
            Falling(Falling &&);
            virtual ~Falling();
            Falling & operator=(const Falling &);
            virtual void enter();
            virtual void leave();
            virtual void update();

        private:
            sf::Vector2f _motion;
    };
}

#endif
