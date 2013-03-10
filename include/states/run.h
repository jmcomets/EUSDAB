#ifndef RUN_H_
#define RUN_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class Run: public CharacterState
    {
        public:
            Run(Character &, float speed, DirectionX, DirectionY);
            Run(const Run &);
            Run(Run &&);
            virtual ~Run();
            Run & operator=(const Run &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    
        private:
            sf::Vector2f _motion;
    };
}

#endif
