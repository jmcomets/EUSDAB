#include <input/joystickmapping.h>
#include <cassert>
#include <iostream>
#include <cmath>

namespace EUSDAB
{
    namespace Input
    {
        static constexpr float STICK_DEAD_ZONE_BOUNDARY = 33;
        static constexpr float TRIGGER_DEAD_ZONE_BOUNDARY = 75;

        JoystickMapping::~JoystickMapping()
        {
            for(auto it : _mappings)
            {
                delete it;
            }
        }

        void JoystickMapping::pushEvent(sf::Event const & e)
        {
            // Store current joystick id
            int id = e.joystickButton.joystickId;

            // Bug fix
            if ((e.type == sf::Event::JoystickButtonPressed
                    || e.type == sf::Event::JoystickButtonReleased
                    || e.type == sf::Event::JoystickConnected
                    || e.type == sf::Event::JoystickDisconnected
                    || e.type == sf::Event::JoystickMoved) == false)
                { return; }

            // Don't f**king care about disconnected joysticks
            if (sf::Joystick::isConnected(id) == false) { return; }

            // Check assertions
            if ( (0 <= id || static_cast<std::size_t>(id) < _mappings.size()
                    || static_cast<std::size_t>(id) < _mappings.size()) == false)
                { return; }

            if (e.type == sf::Event::JoystickMoved)
            {
                sf::Joystick::Axis const & sfAxis = e.joystickMove.axis;
                float joystickPos = sf::Joystick::getAxisPosition(id, sfAxis);
                Axis axis = sfAxisToAxis(sfAxis, joystickPos);
                auto it = _mappings[id]->axisMapping.find(axis);
                if (it != _mappings[id]->axisMapping.end())
                {
                    if (isInDeadZone(axis, joystickPos))
                    {
                        // Push as FallingEdge event
                        Event event(it->second, Event::Full, Event::FallingEdge);
                        _mappings[id]->player->push(event);
                    }
                    else
                    {
                        // Explicitly convert the given parameter
                        //  to an Event::Ratio
                        static auto r = [](Event::Ratio r) { return r; };

                        // Push as RisingEdge event
                        Event event(it->second, r(std::abs(joystickPos)) / r(100));
                        _mappings[id]->player->push(event);
                    }
                }
                else if (axis == Axis::None)
                {
                    std::cout << "Axis::None" << std::endl;
                }
            }
            else if (e.type == sf::Event::JoystickButtonPressed)
            {
                auto it = _mappings[id]->btnMapping.find(e.joystickButton.button);
                if (it != _mappings[id]->btnMapping.end())
                {
                    Event event(it->second, Event::Full, Event::RisingEdge);
                    _mappings[id]->player->push(event);
                }

            }
            else if (e.type == sf::Event::JoystickButtonReleased)
            {
                auto it = _mappings[id]->btnMapping.find(e.joystickButton.button);
                if (it != _mappings[id]->btnMapping.end())
                {
                    Event event(it->second, Event::Full, Event::FallingEdge);
                    _mappings[id]->player->push(event);
                }
            }
        }

        void JoystickMapping::update()
        {
            for (unsigned int i = 0; i < _playerList.size(); ++i)
            {
                for (auto p : _mappings[i]->btnMapping)
                {
                    if (sf::Joystick::isButtonPressed(i, p.first))
                    {
                        Event event(p.second, Event::Full, Event::ContinuousEdge);
                        _mappings[i]->player->push(event);
                    }
                }

                for (auto p : _mappings[i]->axisMapping)
                {
                    if (sf::Joystick::isConnected(i) == false) { continue; }

                    float pos = sf::Joystick::getAxisPosition(i,
                        axisToSfAxis(p.first));
                    if (!isInDeadZone(p.first, pos))
                    {
                        Event event(p.second, Event::Full, Event::ContinuousEdge);
                        _mappings[i]->player->push(event);
                    }
                }
            }
        }

        void JoystickMapping::initMappings()
        {
            for (unsigned int i = 0; i < _playerList.size(); i++)
            {

                _mappings.push_back(new PlayerMapping);
                _mappings[i]->player = _playerList[i];

                _mappings[i]->btnMapping[Button::A] = Event::A;
                _mappings[i]->btnMapping[Button::B] = Event::B;
                _mappings[i]->btnMapping[Button::X] = Event::A; //FIXME
                _mappings[i]->btnMapping[Button::Y] = Event::Up;
                _mappings[i]->btnMapping[Button::Start] = Event::Ground;

                _mappings[i]->axisMapping[Axis::LStickUp]      = Event::Up;
                _mappings[i]->axisMapping[Axis::LStickDown]    = Event::Down;
                _mappings[i]->axisMapping[Axis::LStickLeft]    = Event::Left;
                _mappings[i]->axisMapping[Axis::LStickRight]   = Event::Right;
                //_mappings[i]->axisMapping[Axis::RStickUp]    = Event::Up;
                //_mappings[i]->axisMapping[Axis::RStickDown]  = Event::Down;
                //_mappings[i]->axisMapping[Axis::RStickLeft]  = Event::Left;
                //_mappings[i]->axisMapping[Axis::RStickRight] = Event::Right;
                _mappings[i]->axisMapping[Axis::DPadUp]        = Event::Up;
                _mappings[i]->axisMapping[Axis::DPadDown]      = Event::Down;
                _mappings[i]->axisMapping[Axis::DPadLeft]      = Event::Left;
                _mappings[i]->axisMapping[Axis::DPadRight]     = Event::Right;
                _mappings[i]->axisMapping[Axis::LTrigger]      = Event::Trigger;
                _mappings[i]->axisMapping[Axis::RTrigger]      = Event::Trigger;
            }
        }

        JoystickMapping::Axis JoystickMapping::sfAxisToAxis(sf::Joystick::Axis const & axis, float pos)
        {
            switch (axis)
            {
                case sf::Joystick::X:
                    return (pos < 0) ? Axis::LStickLeft : Axis::LStickRight;

                case sf::Joystick::Y:
                    return (pos < 0) ? Axis::LStickUp : Axis::LStickDown;

                case sf::Joystick::Z:
                    return Axis::LTrigger;

                case sf::Joystick::R:
                    return Axis::RTrigger;

                case sf::Joystick::U:
                    return (pos < 0) ? Axis::RStickLeft : Axis::RStickRight;

                case sf::Joystick::V:
                    return (pos < 0) ? Axis::RStickUp : Axis::RStickDown;

                case sf::Joystick::PovX:
                    return (pos < 0) ? Axis::DPadLeft : Axis::DPadRight;

                case sf::Joystick::PovY:
                    return (pos < 0) ? Axis::DPadUp : Axis::DPadDown;

                default:
                    return Axis::None;
            }
        }

        sf::Joystick::Axis
            JoystickMapping::axisToSfAxis(JoystickMapping::Axis const & axis)
        {
            switch (axis)
            {
                case LStickRight: case LStickLeft: return sf::Joystick::X;
                case LStickUp   : case LStickDown: return sf::Joystick::Y;
                case RStickRight: case RStickLeft: return sf::Joystick::U;
                case RStickUp   : case RStickDown: return sf::Joystick::V;
                case DPadRight  : case DPadLeft  : return sf::Joystick::PovX;
                case DPadUp     : case DPadDown  : return sf::Joystick::PovY;
                case LTrigger   : return sf::Joystick::Z;
                case RTrigger   : return sf::Joystick::R;
                case None       :
                default: return sf::Joystick::PovX;
            }
        }

        bool JoystickMapping::isInDeadZone(Axis const & axis, float pos)
        {
            switch (axis)
            {
                case DPadUp: case DPadDown:
                case DPadLeft: case DPadRight:
                    return false;

                case LStickUp: case LStickLeft:
                case LStickDown: case LStickRight:
                case RStickUp: case RStickLeft:
                case RStickDown: case RStickRight:
                    return std::abs(pos) < STICK_DEAD_ZONE_BOUNDARY;

                case LTrigger: case RTrigger:
                    return pos < TRIGGER_DEAD_ZONE_BOUNDARY;

                case None: default:
                    return true;
            }
        }
    }
}
