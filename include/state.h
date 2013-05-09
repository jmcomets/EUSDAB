#ifndef STATE_H_
#define STATE_H_

#include <input/listener.h>
#include <entity.h>
#include <movement.h>
#include <animation.h>

namespace EUSDAB
{
    class State: public Input::Listener
    {
        public:
            // Shortcuts for subclasses
            typedef Input::Event Event;

            State(State &&) = default;
            State(State const &) = delete;
            State & operator=(State const &) = delete;

            State(const Movement & = Movement(), Entity * = nullptr, 
                    Animation * = nullptr);
            virtual ~State();

            // Helper for subclasses
            void switchState(Movement const &);
            // ...shortcut version
            void switchState(Movement::Flag const &);

            // Get/Set the state's movement
            Movement movement() const;
            void setMovement(const Movement &);

            // Compare States by Movement
            bool operator<(const State &) const;

            // Get/Set the associated Entity
            Entity * entity() const;
            void setEntity(Entity *);

            // Get/Set the animation
            Animation * animation() const;
            void setAnimation(Animation *);

            // onNextFrame -> advance Animation
            virtual void onNextFrame();

        protected:
            // Movement (identification)
            Movement _mvt;

            // State boilerplate
            Entity * _entity;

            // Animation (graphics/physics)
            Animation * _animation;
    };
}

// Specialization of std::hash<EUSDAB::State>

#include <functional>

namespace std
{
    template <>
        struct hash<EUSDAB::State>
    {
        size_t operator()(const EUSDAB::State & x) const
        {
            return hash<EUSDAB::Movement>()(x.movement());
        }
    };
}

#endif
