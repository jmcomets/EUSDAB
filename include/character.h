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
        const Joystick::State & joystickState() const;
        void addState(CharacterStates::BaseState::Id, CharacterStates::BaseState *);
        void state(CharacterStates::BaseState::Id id);
        CharacterStates::BaseState * currentState() const;
        CharacterStates::BaseState * previousState() const;
        CharacterStates::BaseState::Id currentStateId() const;
        CharacterStates::BaseState::Id previousStateId() const;
        const std::string & name();
        void name(const std::string &);
        int damage();
        void damage(int);
        void setIsFlying(bool);
        bool isFlying();

    private:
        Joystick::State _joystickState;
        CharacterStates::BaseState * _previousState;
        CharacterStates::BaseState * _currentState;
        std::map<CharacterStates::BaseState::Id, CharacterStates::BaseState *> _states;
        std::string _name;
        int _damage;
        bool _isflying;
};

#endif
