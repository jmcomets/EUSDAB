#ifndef INPUT_JOYSTICK_MAPPING_H
#define INPUT_JOYSTICK_MAPPING_H

#include <input/mapping.h>
#include <input/event.h>
#include <map>
#include <string>

namespace EUSDAB
{
    namespace Input
    {
        class JoystickMapping: public Mapping
        {
            public:

                typedef unsigned int JoystickInput;
                
                enum Button: JoystickInput
                {
                    A      = 0,
                    B      = 1,
                    X      = 2,
                    Y      = 3,
                    LT     = 4,
                    RT     = 5,
                    Back   = 6,
                    Start  = 7,
                    Menu   = 8,
                    LStick = 9,
                    RStick = 10
                };

                enum Axis: JoystickInput
                {
                    None         = 0,
                    LStickUp     = 1,
                    LStickDown   = 2,
                    LStickRight  = 3,
                    LStickLeft   = 4,
                    RStickUp     = 5,
                    RStickDown   = 6,
                    RStickRight  = 7,
                    RStickLeft   = 8,
                    DPadUp       = 9,
                    DPadDown     = 10,
                    DPadRight    = 11,
                    DPadLeft     = 12
                };


                JoystickMapping(JoystickMapping &&) = default;
                JoystickMapping(JoystickMapping const &) = delete;
                JoystickMapping & operator=(JoystickMapping const &) = delete;

                JoystickMapping();

                template <typename InputIter>
                    JoystickMapping(InputIter begin, InputIter end):
                    Mapping(begin, end), _keyMapping(), _axisMapping()
                {
                    initMappings();
                }

                virtual ~JoystickMapping();

                virtual void pushEvent(sf::Event const & event);
                virtual void update();

            protected:
                void initMappings();
                Axis sfAxisToAxis(sf::Joystick::Axis const & axis, float pos);
                sf::Joystick::Axis axisToSfAxis(Axis const &);
                bool isInDeadZone(Axis const & axis, float pos);

            private:
                //FIXME change int into Button + add sfButtonToButton method
                std::map<int, std::pair<Speaker *, Event::Id>> _keyMapping;
                std::map<Axis,
                    std::pair<Speaker *, Event::Id>> _axisMapping;
                //std::vector<int, std::map<Axis, 

                std::map<sf::Joystick::Axis, 
                    std::pair<std::string, bool (*)(float const &)>> _axis;
        };
    }
}

#endif
