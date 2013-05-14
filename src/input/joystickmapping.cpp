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

        void JoystickMapping::pushEvent(const sf::Event & e)
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
            assert(0 <= id);
            assert(static_cast<std::size_t>(id) < _axisMapping.size());
            assert(static_cast<std::size_t>(id) < _btnMapping.size());

            if (e.type == sf::Event::JoystickMoved)
            {
                const sf::Joystick::Axis & sfAxis = e.joystickMove.axis;
                float joystickPos = sf::Joystick::getAxisPosition(id, sfAxis);
                Axis axis = sfAxisToAxis(sfAxis, joystickPos);
                auto it = _axisMapping[id].second.find(axis);
                if (it != _axisMapping[id].second.end())
                {
                    if (isInDeadZone(axis, joystickPos))
                    {
                        // Push as FallingEdge event
                        Event event(it->second, Event::Full, Event::FallingEdge);
                        _axisMapping[id].first->push(event);
                    }
                    else
                    {
                        // Explicitly convert the given parameter
                        //  to an Event::Ratio
                        static auto r = [](Event::Ratio r) { return r; };

                        // Push as RisingEdge event
                        Event event(it->second, r(std::abs(joystickPos)) / r(100));
                        _axisMapping[id].first->push(event);
                    }
                }
                else if (axis == Axis::None)
                {
                    std::cout << "Axis::None" << std::endl;
                }
            }
            else if (e.type == sf::Event::JoystickButtonPressed)
            {
                auto it = _btnMapping[id].second.find(e.joystickButton.button);
                if (it != _btnMapping[id].second.end())
                {
                    Event event(it->second, Event::Full, Event::RisingEdge);
                    _btnMapping[id].first->push(event);
                }
            }
            else if (e.type == sf::Event::JoystickButtonReleased)
            {
                auto it = _btnMapping[id].second.find(e.joystickButton.button);
                if (it != _btnMapping[id].second.end())
                {
                    Event event(it->second, Event::Full, Event::FallingEdge);
                    _btnMapping[id].first->push(event);
                }
            }
        }

        void JoystickMapping::update()
        {
            for (unsigned int i = 0; i < _playerList.size(); ++i)
            {
                for (auto p : _btnMapping[i].second)
                {
                    if (sf::Joystick::isButtonPressed(i, p.first))
                    {
                        Event event(p.second, Event::Full, Event::ContinuousEdge);
                        _btnMapping[i].first->push(event);
                    }
                }

                for (auto p : _axisMapping[i].second)
                {
                    if (sf::Joystick::isConnected(i) == false) { continue; }

                    float pos = sf::Joystick::getAxisPosition(i,
                        axisToSfAxis(p.first));
                    if (!isInDeadZone(p.first, pos))
                    {
                        Event event(p.second, Event::Full, Event::ContinuousEdge);
                        _axisMapping[i].first->push(event);
                    }
                }
            }
        }
        
        void JoystickMapping::initMappings()
        {
            for (unsigned int i = 0; i < _playerList.size(); i++)
            {
                _btnMapping.emplace_back(_playerList[i],
                        std::map<int, Event::Id>());

                _btnMapping[i].second[Button::A] = Event::A;
                _btnMapping[i].second[Button::B] = Event::B;
                _btnMapping[i].second[Button::X] = Event::X;
                _btnMapping[i].second[Button::Y] = Event::Y;
                _btnMapping[i].second[Button::Start] = Event::Ground;

                _axisMapping.emplace_back(_playerList[i], 
                        std::map<Axis, Event::Id>());

                _axisMapping[i].second[Axis::LStickUp]      = Event::Up;
                _axisMapping[i].second[Axis::LStickDown]    = Event::Down;
                _axisMapping[i].second[Axis::LStickLeft]    = Event::Left;
                _axisMapping[i].second[Axis::LStickRight]   = Event::Right;
                //_axisMapping[i].second[Axis::RStickUp]    = Event::Up;
                //_axisMapping[i].second[Axis::RStickDown]  = Event::Down;
                //_axisMapping[i].second[Axis::RStickLeft]  = Event::Left;
                //_axisMapping[i].second[Axis::RStickRight] = Event::Right;
                //_axisMapping[i].second[Axis::DPadUp]      = Event::Up;
                //_axisMapping[i].second[Axis::DPadDown]    = Event::Down;
                //_axisMapping[i].second[Axis::DPadLeft]    = Event::Left;
                //_axisMapping[i].second[Axis::DPadRight]   = Event::Right;
                _axisMapping[i].second[Axis::LTrigger]      = Event::Trigger;
                _axisMapping[i].second[Axis::RTrigger]      = Event::Trigger;
            }
        }

        JoystickMapping::Axis JoystickMapping::sfAxisToAxis(const sf::Joystick::Axis & axis, float pos)
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
            JoystickMapping::axisToSfAxis(const JoystickMapping::Axis & axis)
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

        bool JoystickMapping::isInDeadZone(const Axis & axis, float pos)
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
