#ifndef STATE_H
#define STATE_H

#include <listener.h>

class Entity;
class Speaker;

class State: public Listener
{
    public:
        enum Id
        {
            Idle,
            Jump,
            Left,
            Right
        };

        explicit State(State &&) = default;
        explicit State(State const &) = delete;
        State & operator=(State const &) = delete;

        explicit State(Entity * entity, Speaker * speaker);
        virtual ~State();

        template <typename TState, typename... Args>
        virtual void switchState(State::Id const &, Args&&... args)
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

#endif

