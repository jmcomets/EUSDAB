#ifndef CHARACTER_STATE_H_
#define CHARACTER_STATE_H_

#include <SFML/Window/Input.hpp>
#include <view.h>

class Character;

class CharacterState
{
    public:
        enum Id {};
        CharacterState();
        CharacterState(const CharacterState &);
        CharacterState(CharacterState &&);
        virtual ~CharacterState();
        CharacterState & operator=(const CharacterState &);
        void enter();
        void leave();
        void update(const Input &);
        View & view();

    protected:
        Character _character;
        view _view;
};

#endif // CHARACTER_STATE_H_
