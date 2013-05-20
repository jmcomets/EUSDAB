#ifndef MOVEMENT_H_
#define MOVEMENT_H_

namespace EUSDAB
{
    // Identifier-type used to define the different states
    //   accessible and their id.
    class Movement
    {
        public:
            // Flag combining both Action and Direction
            typedef unsigned int Flag;

            enum Direction: Flag
            {
                Up    = 1 << 0,
                Down  = 1 << 1,
                Left  = 1 << 2,
                Right = 1 << 3,

                // Used to lookup the size, as well as for initialization
                None  = 1 << 4
            };

            enum Action: Flag
            {
                Idle        = 1 << 5 ,
                Jump        = 1 << 6 ,
                Attack      = 1 << 7 ,
                Smash       = 1 << 8 ,
                Flee        = 1 << 9 ,
                Shield      = 1 << 10,
                OnHit       = 1 << 11,
                Walk        = 1 << 12,
                Run         = 1 << 13,
                Falling     = 1 << 14,
                Crouch      = 1 << 15,
                AerialHit   = 1 << 16,
                Special     = 1 << 17,
                Stunned     = 1 << 19,

                // Used to lookup the size, as well as for initialization
                Noop        = 1 << 20 
            };

            Movement(Movement &&) = default;
            Movement(const Movement &) = default;
            ~Movement() = default;
            Movement & operator=(const Movement &) = default;

            Movement(Flag = static_cast<Flag>(0));
            Movement(Action, Direction);

            // Get/Set the flag
            Flag flag() const;
            void setFlag(Flag);

            // Convert Flag -> Action
            Action toAction(Flag) const;

            // Convert Flag -> Direction
            Direction toDirection(Flag) const;

            // Get/Set the action
            Action action() const;
            void setAction(Action);

            // Get/Set the direction
            Direction direction() const;
            void setDirection(Direction);

            operator Flag() const;
            bool operator<(const Movement &) const;

        private:
            Action _action;
            Direction _direction;
    };
}

// Specialization of std::hash<EUSDAB::Movement>

#include <functional>

namespace std
{
    template <>
        struct hash<EUSDAB::Movement>
    {
        size_t operator()(const EUSDAB::Movement & x) const
        {
            return hash<EUSDAB::Movement::Flag>()(x.flag());
        }
    };
}

#endif
