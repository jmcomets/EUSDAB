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
                State() = delete;
                State(Entity * entity, Speaker * speaker);
                State(State &&) = default;
                State(State const &) = delete;
                virtual ~State();
                State & operator=(State const &) = delete;

                // FIXME forward declaration messes this up
                template <typename TState, typename... Args>
                    void switchState(Movement const & id, Args&&... args)
                    {
                        State * s = _entity->state(id);
                        if(s == nullptr)
                        {
                            s = new TState(_entity, _speaker, args...);
                            _entity->state(id, s);
                        }
                        _speaker->setListener(s);
                        _entity->state(s);
                    }

            protected:
                Entity * _entity;
                Speaker * _speaker;
        };
    }
}

#endif

