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
            IdleRight, IdleLeft,
            WalkLeft, WalkRight,
            AerialDodgeLeft, AerialDodgeRight,
            AerialHitLeft, AerialHitRight,
            CrouchLeft, CrouchRight,
            DodgeLeft, DodgeRight,
            EjectedLeft, EjectedRight,
            FallingLeft, FallingRight,
            GuardLeft, GuardRight,
            HelplessLeft, HelplessRight,
            Jump1Left, Jump1Right,
            Jump2Left, Jump2Right,
            LandingLeft, LandingRight,
            RunLeft, RunRight,
            SmashDown, SmashLeft, SmashRight, SmashUp,
            SpecialDown, SpecialLeft, SpecialRight, SpecialUp,
            AttackDown, AttackLeft, AttackRight, AttackUp,
            AerialSpecialDown, AerialSpecialLeft, AerialSpecialRight, AerialSpecialUp,
            AerialAttackDown, AerialAttackLeft, AerialAttackRight, AerialAttackUp
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
