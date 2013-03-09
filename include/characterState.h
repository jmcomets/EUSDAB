#ifndef CHARACTER_STATE_H_
#define CHARACTER_STATE_H_

#include <view.h>
#include <hitbox.h>
#include <joystickState.h>

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

        enum DirectionY { Up, Down };
        enum DirectionX { Left, Right };

        CharacterState(Character &, DirectionX = Right, DirectionY = Down);
        CharacterState(CharacterState &&);
        CharacterState(const CharacterState &);
        virtual ~CharacterState();
        CharacterState & operator=(const CharacterState &);

        virtual void update(const JoystickState &);
        virtual void enter();
        virtual void leave();

        View & view();
        bool isDirection(DirectionX) const;
        bool isDirection(DirectionY) const;

    protected:
        Character & _character;
        View * _view;
        Geometry::Hitbox * _hitbox;

    private:
        std::pair<DirectionX, DirectionY> _direction;
};

#endif // CHARACTER_STATE_H_
