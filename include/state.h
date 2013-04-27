#ifndef INPUT_STATE_H_
#define INPUT_STATE_H_

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

            State();
            State(Entity * entity, Input::Speaker * speaker);
            virtual ~State();

            Entity * entity() const;
            Entity * entity(Entity *);

            void switchState(Movement const &);

            typedef Input::Event Event;

        protected:
            Entity * _entity;
            Input::Speaker * _speaker;
    };
}

#endif
