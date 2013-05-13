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
                    A, B,
                    X, Y,
                    LB, RB,
                    LStick, RStick,
                    Back, Start, Menu
                };

                enum Axis: JoystickInput
                {
                    LStickUp, LStickDown,
                    LStickRight, LStickLeft,
                    RStickUp, RStickDown,
                    RStickRight, RStickLeft,
                    DPadUp, DPadDown,
                    DPadRight, DPadLeft,
                    LTrigger, RTrigger,
                    None
                };

                JoystickMapping() = delete;
                JoystickMapping(JoystickMapping &&) = default;
                JoystickMapping(const JoystickMapping &) = delete;
                JoystickMapping & operator=(const JoystickMapping &) = delete;

                template <typename InputIter>
                    JoystickMapping(InputIter begin, InputIter end):
                    Mapping(begin, end), _btnMapping(), _axisMapping()
                {
                    initMappings();
                }

                ~JoystickMapping() = default;

                // Event-based input, mapping SFML events to
                //  EUSDAB events, using a predefined mapping
                void pushEvent(const sf::Event & event);

                // Continuous input using the same mapping
                //  as for the event-based version
                void update();

            protected:
                // Setup the mappings (ugly s**t)
                void initMappings();

                // SFML Joystick axis -> EUSDAB Joystick axis
                Axis sfAxisToAxis(const sf::Joystick::Axis &, float);

                // EUSDAB Joystick axis -> SFML Joystick axis
                sf::Joystick::Axis axisToSfAxis(const Axis &);

                // Return if the given axis event is in the "dead" zone,
                //  that is if it should be considered as at rest
                bool isInDeadZone(const Axis &, float);

            private:
                std::vector<std::pair<Speaker *, std::map<int, Event::Id>>> _btnMapping;
                std::vector<std::pair<Speaker *, std::map<Axis, Event::Id>>> _axisMapping;
        };
    }
}

#endif
