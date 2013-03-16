#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <input/listener.h>
#include <input/speaker.h>

namespace EUSDAB
{
    class Entity;

    namespace Input
    {
        class State: public Listener
        {
            public:
                enum Movement
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

                typedef int Id;

                State() = delete;
                State(Entity * entity, Speaker * speaker);
                State(State &&) = default;
                State(const State &) = delete;
                virtual ~State();
                State & operator=(const State &) = delete;

                // FIXME forward declaration messes this up
                template <typename TState, typename... Args>
                    void switchState(const State::Id &, Args&&... args)
                {
                    State * s = _entity->state(id);
                    if(s == nullptr)
                    {
                        s = new TState(_entity, _speaker, args...);
                        _entity->addState(id, s);
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

