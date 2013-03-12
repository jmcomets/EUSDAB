#include <joystick.h>
#include <stdexcept>
#include <SFML/Window/Joystick.hpp>

namespace Joystick
{
    // Default Joystick configuration
    static const Button defaultConfig[NbButtons] = {
        ButtonY,      // 0
        ButtonX,      // 1
        ButtonA,      // 2
        ButtonB,      // 3
        ButtonZ,      // 4
        TriggerRight, // 5
        TriggerLeft,  // 6
        Other,        // 7
        Other,        // 8
        Other,        // 9
        Other,        // 10
        Other,        // 11
        Other,        // 12
        Other,        // 13
        Other,        // 14
        Other,        // 15
        Other,        // 16
        Other,        // 17
        Other,        // 18
        Other,        // 19
        Other,        // 20
        Other,        // 21
        Other,        // 22
        Other,        // 23
        Other,        // 24
        Other,        // 25
        Other,        // 26
        Other,        // 27
        Other,        // 28
        Other,        // 29
        Other,        // 30
        Other         // 31
    };

    // Joystick::ButtonConfig implementation
    unsigned int ButtonConfig::operator[](Button btn) const
    {
        for (unsigned int i = 0; i < _btnConfig.size(); i++)
        {
            if (btn == _btnConfig[i])
            {
                return i;
            }
        }
        throw std::runtime_error("Unhandled Button -> id mapping");
    }

    // Joystick::State implementation
    State::State(unsigned int id):
        _id(id), _frameMasks(),
        _btnConfig(defaultConfig, defaultConfig + NbButtons) {}

    bool State::isConnected() const
    {
        return sf::Joystick::isConnected(_id);
    }

    unsigned int State::id() const
    {
        return _id;
    }

    float State::axisPosition(Axis axis) const
    {
        return sf::Joystick::getAxisPosition(_id,
                axis == X ? sf::Joystick::X : sf::Joystick::Y);
    }

    bool State::isButtonDown(Button btn) const
    {
        return btn != Other && sf::Joystick::isButtonPressed(_id, _btnConfig[btn]);
    }

    bool State::isButtonUp(Button btn) const
    {
        return isButtonDown(btn) == false;
    }

    bool State::isAxisFront(Axis axis) const
    {
        return _frameMasks.back()[btn]
    }

    bool State::isButtonFront(Button btn) const
    {
    }

    // Joystick::State::Mask implementation
    State::Mask::Mask(const ButtonConfig & config):
        _btnConfig(config),
        _btns(), _axes(false, false)
    {
    }
}
