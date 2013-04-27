#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <functional>

namespace EUSDAB
{
    // Identifier-type used to define the different states
    //   accessible and their id.
    // Specializes std::hash<Movement>
    class Movement
    {
        public:
            typedef unsigned int Flag;
            typedef std::hash<Flag> Hash;

            enum Direction: Flag
            {
                None  = 1 << 0,
                Up    = 1 << 1,
                Down  = 1 << 2,
                Left  = 1 << 3,
                Right = 1 << 4,
            };

            enum Action: Flag
            {
                Noop   = 1 << 5,
                Idle   = 1 << 6,
                Jump   = 1 << 7,
                Attack = 1 << 8,
                Smash  = 1 << 9,
                Flee   = 1 << 10,
                Guard  = 1 << 11,
                OnHit  = 1 << 12,
            };

            Movement(Movement &&) = default;
            Movement(Movement const &) = default;
            ~Movement() = default;
            Movement & operator=(Movement const &) = default;

            Movement(Flag = 0);

            Flag flag() const;
            void setFlag(Flag);

            operator Flag() const;
            bool operator<(const Movement &) const;

        private:
            Flag _flag;
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
