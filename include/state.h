#ifndef INPUT_STATE_H_
#define INPUT_STATE_H_

#include <functional>
#include <movement.h>
#include <entity.h>
#include <input/listener.h>
#include <input/speaker.h>

namespace EUSDAB
{
    class State: public Input::Listener
    {
        public:
            State(State &&) = default;
            State(State const &) = delete;
            State & operator=(State const &) = delete;

            State(Entity * entity = nullptr,
                    Input::Speaker * speaker = nullptr,
                    const Movement & = Movement());
            virtual ~State();

            Entity * entity() const;
            Entity * entity(Entity *);

            void switchState(Movement const &);

            // Shortcut for derived classes
            typedef Input::Event Event;

            // Get/Set the state's movement
            Movement movement() const;
            void setMovement(const Movement &);

            // ID boilerplate
            bool operator<(const State &) const;

        protected:
            Movement _mvt;
            Entity * _entity;
            Input::Speaker * _speaker;
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
