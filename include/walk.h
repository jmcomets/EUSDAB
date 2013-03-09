#ifndef WALK_H_
#define WALK_H_

#include <characterState.h>
#include <SFML/System/Vector2.hpp>

class Walk: public CharacterState
{
    public:
		Walk(Character &, float speed, DirectionX, DirectionY);
        Walk(const Walk &);
        Walk(Walk &&);
        virtual ~Walk();
        Walk & operator=(const Walk &);
        virtual void enter();
        virtual void leave();
        virtual void update();
	
		private:
		sf::Vector2f _motion;
};

#endif
