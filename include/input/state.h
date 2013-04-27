#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <movement.h>
#include <entity.h>

#include <input/listener.h>
#include <input/speaker.h>

namespace EUSDAB
{
    namespace Input
    {
        class State: public Listener
        {
            public:
                State(State &&) = default;
                State(State const &) = delete;
                State & operator=(State const &) = delete;

                State();
                State(Entity * entity, Speaker * speaker);
                virtual ~State();

                Entity * entity() const;
                Entity * entity(Entity *);

                void switchState(Movement const &);

            protected:
                Entity * _entity;
                Speaker * _speaker;
        };
    }
}

#endif

