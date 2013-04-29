#ifndef INPUT_STATE_H_
#define INPUT_STATE_H_

#include <functional>
#include <movement.h>
#include <entity.h>
#include <input/listener.h>
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

            State(Entity * = nullptr, const Movement & = Movement());
            virtual ~State();

            // Helper for subclasses
            void switchState(Movement const &);

            // Movement module

            // Get/Set the state's movement
            Movement movement() const;
            void setMovement(const Movement &);

            // Compare States by Movement
            bool operator<(const State &) const;

            // Get/Set the associated Entity
            Entity * entity() const;
            void setEntity(Entity *);

            // Get the animation
            Animation & animation();
            // ...const version
            const Animation & animation() const;

        protected:
            // State boilerplate
            Entity * _entity;

            // Movement (identification)
            Movement _mvt;

            // Animation (graphics/physics)
            Animation _animation;
    };
}

// Specialization of std::hash<EUSDAB::State>
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
