#ifndef CHARACTER_STATE_H_
#define CHARACTER_STATE_H_

#include <SFML/Window/Input.hpp>
#include <view.h>
#include <hitbox.h>

class Character;

class CharacterState
{
    public:
        enum Id
        {
            AerialAttack, AerialDodge,
            AerialHit, AerialSpecial,
            AttackDash, Attack,
            Character, Crouch,
            Dodge, Ejected,
            Entity, Falling,
            Guard, Helpless,
            Idle, Item,
            Jump1, Jump2,
            Landing, Run, Walk
            Smash, Special,
        };

        CharacterState(Character &);
        CharacterState(CharacterState &&);
        CharacterState(const CharacterState &);
        virtual ~CharacterState();
        CharacterState & operator=(const CharacterState &);

        virtual void update(const sf::Input &);
        virtual void enter();
        virtual void leave();
        View & view();

    protected:
        Character & _character;
        View * _view;
        Hitbox * _hitbox;
};

#endif // CHARACTER_STATE_H_
