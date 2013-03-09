#ifndef RUN_H_
#define RUN_H_

#include <characterState.h>

class Run: public CharacterState
{
    public:
        Run(Character &, float speed, directionX, directionY);
        Run(const Run &);
        Run(Run &&);
        virtual ~Run();
        Run & operator=(const Run &);
        virtual void enter();
        virtual void leave();
        virtual void update(const JoystickState &);

	private:
		sf::Vector2f _motion;
};

#endif
