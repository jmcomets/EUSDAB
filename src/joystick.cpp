#include <joystick.h>
#include <SFML/Window/Joystick.hpp>

namespace Joytick
{
    // Number of joysticks handled by SFML
    static const unsigned int nbJoysticks = 8;

    // Number of buttons handled by SFML
    static const unsigned int nbButtons = 32;

    // Default Joystick configuration
    static const Button defaultConfig[nbButtons] = {
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

    // Joystick::State implementation
    State::State(unsigned int id):
        _id(id), _btnConfig(defaultConfig, defaultConfig + nbButtons)
    {
        init();
    }

    inline void init()
    {
        _btnsUp[ButtonA] = false;
        _btnsUp[ButtonB] = false;
        _btnsUp[ButtonZ] = false;
        _btnsUp[ButtonY] = false;
        _btnsUp[TriggerLeft] = false;
        _btnsUp[TriggerRight] = false;
        _btnsUp[Other] = false;
        _axesUp.first = false;
        _axesUp.second = false;
    }

    inline bool State::isConnected() const
    {
        return sf::Joystick::IsConnected(_id);
    }

    inline bool State::isAxisFront(Axis axis) const
    {
        return axis == X ? _axesUp.first : _axesUp.second;
    }

    float State::axisPosition(Axis axis) const
    {
        return sf::Joystick::getAxisPosition(_id,
                axis == X ? sf::Joystick::X : sf::Joystick::Y);
    }

    bool State::isButtonFront(Button btn) const
    {
        if (btn != Other)
        {
            auto it = _btnsUp.find(btn);
            if (it != _btnsUp.end())
            {
                return it->second;
            }
        }
        return false;
    }

    bool State::isButtonDown(Button btn) const
    {
        if (btn != Other)
        {
            for (std::vector<Button>::size_type i = 0; i < _btnConfig.size(); i++)
            {
                if (_btnConfig[i] == btn 
                        && sf::Joystick::isButtonPressed(_id, i))
                {
                    return true;
                }
            }
        }
        return false;
    }

    inline bool State::isButtonUp(Button btn) const
    {
        return isButtonDown(btn) == false;
    }

    unsigned int State::id() const
    {
        return _id;
    }
}