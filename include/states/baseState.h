#ifndef CHARACTER_STATE_H_
#define CHARACTER_STATE_H_

#include <view.h>
#include <hitbox.h>
#include <joystick.h>

class Character;

namespace CharacterStates
{
    class BaseState
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
                StunnedLeft, StunnedRight,
                HelplessLeft, HelplessRight,
                JumpLeft, JumpRight,
                LandingLeft, LandingRight,  //those are idle type states
                RunLeft, RunRight,
                SmashDown, SmashLeft, SmashRight, SmashUp,
                SpecialDown, SpecialLeft, SpecialRight, SpecialUp,
                AttackDown, AttackLeft, AttackRight, AttackUp,
                AerialSpecialDown, AerialSpecialLeft, AerialSpecialRight, AerialSpecialUp,
                AerialAttackDown, AerialAttackLeft, AerialAttackRight, AerialAttackUp
            };

            enum DirectionY { Up, Down };
            enum DirectionX { Left, Right };

            BaseState(Character &, DirectionX = Right, DirectionY = Down);
            BaseState(BaseState &&);
            BaseState(const BaseState &);
            virtual ~BaseState();
            BaseState & operator=(const BaseState &);

            virtual void update();
            virtual void enter();
            virtual void leave();

            View & view();
            bool isDirection(DirectionX) const;
            bool isDirection(DirectionY) const;

        protected:
            Character & _character;
            std::shared_ptr<View> _view;
            Geometry::Hitbox * _hitbox;

        private:
            std::pair<DirectionX, DirectionY> _direction;
    };
}

#endif // CHARACTER_STATE_H_
