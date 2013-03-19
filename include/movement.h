#ifndef MOVEMENT_H_
#define MOVEMENT_H_

namespace EUSDAB
{
    // TODO comment this class
    struct Movement
    {
        enum Direction
        {
            Up = 0x01 << 0,
            Down = 0x02 << 0,
            Left = 0x03 << 0,
            Right = 0x04 << 0
        };

        enum Action
        {
            Idle = 0x01 << 2,
            Jump = 0x02 << 2,
            Attack = 0x03 << 2,
            Smash = 0x04 << 2,
            Flee = 0x05 << 2,
            Guard = 0x06 << 2,
            OnHit = 0x07 << 2
        };

        Movement(Movement::Action, Movement::Direction);
        Movement() = delete;
        Movement(Movement &&) = default;
        Movement(const Movement &) = default;
        ~Movement() = default;
        Movement & operator=(const Movement &) = default;

        operator int() const;

        Movement::Action action;
        Movement::Direction direction;
    };
}

#endif
