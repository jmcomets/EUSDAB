#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <map>
#include <entity.h>
#include <states/baseState.h>
#include <joystick.h>

class Character: public Entity
{
    public:
        Character();
        Character(const Character &);
        Character(Character &&);
        virtual ~Character();
        Character & operator=(const Character &);
        void update();
        void render(Graphics::Target &, Graphics::RenderStates);
        void addState(CharacterStates::BaseState::Id, CharacterStates::BaseState *);
        void state(CharacterStates::BaseState::Id id);
        std::string const & name();
        void name(std::string const &);
        int damage();
        void damage(int);
        const Joystick::State & joystickState() const;

    private:
        CharacterStates::BaseState * _currentState;
        Joystick::State _joystickState;
        std::map<CharacterStates::BaseState::Id, CharacterStates::BaseState *> _states;
        std::string _name;
        int _damage;
};

#endif
