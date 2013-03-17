#ifndef MOVEMENT_H
#define MOVEMENT_H

namespace EUSDAB
{
    struct Movement
    {
        enum Action
        {
            Idle, Jump,
            Attack, Smash,
            Flee, Guard,
            OnHit
        };

        enum Direction
        {
            Up, Down,
            Left, Right
        };

        explicit Movement() = delete;
        explicit Movement(Movement const &) = default;
        Movement & operator=(Movement const &) = default;
        ~Movement() = default;

        explicit Movement(Movement::Action, Movement::Direction);

        operator int() const;

        Movement::Action action;
        Movement::Direction direction;
    };
}

#endif

