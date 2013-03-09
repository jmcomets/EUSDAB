#ifndef JOYSTICK_STATE_H_
#define JOYSTICK_STATE_H_

#include <array>
#include <utility>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

#define SFML_NB_BUTTONS 32
#define SFML_NB_JOYSTICKS 8

class JoystickState
{
    public:
        JoyStickState();
        JoyStickState(JoyStickState &&);
        JoyStickState(const JoyStickState &);
        ~JoyStickState();
        JoyStickState & operator=(const JoyStickState &);

        enum Axis { X, Y };

        bool isConnected(unsigned int joyId) const;
        bool isButtonFront(unsigned int joyId, unsigned int btnId) const;
        bool isAxisFront(unsigned int joyId, Axis axis) const;
        bool isButtonUp(unsigned int joyId, unsigned int btnId) const;
        bool isButtonDown(unsigned int joyId, unsigned int btnId) const;
        float axisPosition(Axis axis) const;

    private:
        std::array<std::array<bool, SFML_NB_BUTTONS>, SFML_NB_JOYSTICKS> _joyBtnsPressed;
        std::array<std::pair<bool, bool>, SFML_NB_JOYSTICKS> _joyAxesUp;
};

#endif
