#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <map>
#include <entity.h>
#include <characterState.h>
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
        void addState(CharacterState::Id, CharacterState *);
        void state(CharacterState::Id id);
        std::string const & name();
        void name(std::string const &);
        int damage();
        void damage(int);
        const Joystick::State & joystickState() const;

    private:
        CharacterState * _currentState;
        Joystick::State _joystickState;
        std::map<CharacterState::Id, CharacterState *> _states;
        std::string _name;
        int _damage;
};

#endif
