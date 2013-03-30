#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <functional>

namespace EUSDAB
{
    // Identifier-type used to define the different states
    //   accessible and their id.
    // Specializes std::hash<Movement>
    struct Movement
    {
        typedef unsigned int Flag;
        typedef std::hash<Flag> Hash;

        // TODO check if combination of directions is possible
        enum Direction: Flag
        {
            Up = 0x01 << 0,
            Down = 0x02 << 0,
            Left = 0x03 << 0,
            Right = 0x04 << 0
        };

        enum Action: Flag
        {
            Idle = 0x01 << 2,
            Jump = 0x02 << 2,
            Attack = 0x03 << 2,
            Smash = 0x04 << 2,
            Flee = 0x05 << 2,
            Guard = 0x06 << 2,
            OnHit = 0x07 << 2
        };

        Movement() = delete;
        Movement(Movement &&) = default;
        Movement(Movement const &) = default;
        ~Movement() = default;
        Movement & operator=(Movement const &) = default;

        Movement(Action, Direction);

        operator Flag() const;

        Action action;
        Direction direction;
    };
}

// Specialization of std::hash<EUSDAB::Movement>
namespace std
{
    template <>
        struct hash<EUSDAB::Movement>
        {
            size_t operator()(const EUSDAB::Movement & x) const
            {
                return hash<EUSDAB::Movement::Flag>()(x);
            }
        };
}

#endif
