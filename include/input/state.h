#ifndef INPUT_STATE_H
#define INPUT_STATE_H

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
                enum Movement
                {
                    Idle,
                    Jump,
                    Attack,
                    Smash,
                    Flee,
                    Guard,
                    OnHit
                };

                enum Direction
                {
                    Up,
                    Down,
                    Left,
                    Right
                };

                typedef int Id;

                explicit State() = delete;
                explicit State(State &&) = default;
                explicit State(State const &) = delete;
                State & operator=(State const &) = delete;

                explicit State(Entity * entity, Speaker * speaker);
                virtual ~State();

                template <typename TState, typename... Args>
                    void switchState(State::Id const &, Args&&... args)
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

