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
        Character(Character &&) = default;
        virtual ~Character();
        Character & operator=(const Character &);

        // Entity boilerplate
        void update();
        void render(Graphics::Target &, Graphics::RenderStates);

        // Get joystick attached to character
        const Joystick::State & joystickState() const;
        bool addState(CharacterStates::BaseState::Id, CharacterStates::BaseState *);
        void state(CharacterStates::BaseState::Id id);

        // Lookup states
        const CharacterStates::BaseState * currentState() const;
        const CharacterStates::BaseState * previousState() const;

        // Lookup state id's
        CharacterStates::BaseState::Id currentStateId() const;
        CharacterStates::BaseState::Id previousStateId() const;

        const std::string & name() const;
        const std::string & name(const std::string &);
        int damage() const;
        int damage(int);
        bool isFlying() const;
        bool isFlying(bool);
        unsigned int shieldCapacity() const;
        unsigned int shieldCapacity(unsigned int);
        unsigned int decreaseShieldCapacity(unsigned int = 1);
        unsigned int incraseShieldCapacity(unsigned int = 1);

    private:
        Joystick::State _joystickState;
        CharacterStates::BaseState * _previousState;
        CharacterStates::BaseState * _currentState;
        std::map<CharacterStates::BaseState::Id, CharacterStates::BaseState *> _states;
        std::string _name;
        unsigned int _damage;
        bool _isFlying;
        unsigned int _shieldCapacity;
};

#endif
