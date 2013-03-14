#include <state.h>

State::State(Entity * entity, Speaker * speaker);
    _entity(entity),
    _speaker(speaker)
{
}

State::~State()
{
}

