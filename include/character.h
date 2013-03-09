#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <entity.h>

class Character: public Entity
{
    public:
        Character();
        Character(const Character &);
        Character(Character &&);
        virtual ~Character();
        Character & operator=(const Character &);

    private:
        CharacterState * _state;
};

#endif // CHARACTER_H_
