#ifndef STATE_H
#define STATE_H

#include <listener.h>

class Speaker;

class State : public Listener {
    public:
        class enum State {Idle, Jump, Left, Right};

        explicit State(State const &) = delete;
        State & operator=(State const &) = delete;

        virtual ~State();

        virtual void change_state(State::State const &);

    protected:
        Speaker * _speaker;
};

#endif

