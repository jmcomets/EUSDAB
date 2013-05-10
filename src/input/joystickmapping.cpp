#include <input/joystickmapping.h>
#include <cassert>
#include <iostream>

namespace EUSDAB
{
    namespace Input
    {
        JoystickMapping::JoystickMapping() : Mapping(), _keyMapping()
        {
        }

        JoystickMapping::~JoystickMapping()
        {
        }

        void JoystickMapping::pushEvent(sf::Event const & e)
        {
            if (e.type == sf::Event::JoystickMoved)
            {
                sf::Joystick::Axis axis = e.joystickMove.axis;
                float p = sf::Joystick::getAxisPosition(e.joystickButton.joystickId, axis);
                Axis a = sfAxisToAxis(axis, p);
                auto it = _axisMapping.find(a);
                if(it != _axisMapping.end())
                {
                    if(isInDeadZone(a, p))
                    {
                        std::cout << "IS IN DEAD ZONE : " << p << std::endl;
                        Event event(it->second.second, Event::Full, Event::FallingEdge);
                        it->second.first->push(event);
                    }
                    else
                    {
                        Event event(it->second.second, (p > 0 ? p : -p) / 100, Event::RisingEdge);
                        it->second.first->push(event);
                    }
                }
                else if(a == Axis::None)
                {
                    std::cout << "Axis::None" << std::endl;
                }
            }
            else if(e.type == sf::Event::JoystickButtonPressed)
            {
                auto it = _keyMapping.find(e.joystickButton.button);
                if(it != _keyMapping.end())
                {
                    Event event(it->second.second, Event::Full, Event::RisingEdge);
                    it->second.first->push(event);
                }
            }
            else if(e.type == sf::Event::JoystickButtonReleased)
            {
                auto it = _keyMapping.find(e.joystickButton.button);
                if(it != _keyMapping.end())
                {
                    Event event(it->second.second, Event::Full, Event::FallingEdge);
                    it->second.first->push(event);
                }
            }
        }

        void JoystickMapping::update()
        {
            // Handle continuous input
            for (auto p : _keyMapping)
            {
                if (sf::Joystick::isButtonPressed(0, p.first))
                {
                    Event event(p.second.second, Event::Full, Event::ContinuousEdge);
                    p.second.first->push(event);
                }
            }
            for (auto p : _axisMapping)
            {
                float pos = sf::Joystick::getAxisPosition(0,
                    axisToSfAxis(p.first));
                if(!isInDeadZone(p.first, pos))
                {
                    Event event(p.second.second, Event::Full, Event::ContinuousEdge);
                    p.second.first->push(event);
                }
            }
        }
        

        void JoystickMapping::initMappings()
        {
            //assert (_playerList.size() > 1);

            //_axis[sf::Joystick::X] = std::make_pair("x", [](float const & x) { return std::abs(x) > 20; });
            //_axis[sf::Joystick::Y] = std::make_pair("y", [](float const & x) { return std::abs(x) > 20; });
            //_axis[sf::Joystick::Z] = std::make_pair("z", [](float const & x) { return x > -98; });
            //_axis[sf::Joystick::R] = std::make_pair("r", [](float const & x) { return std::abs(x) > 20; });
            //_axis[sf::Joystick::U] = std::make_pair("u", [](float const & x) { return std::abs(x) > 20; });
            //_axis[sf::Joystick::V] = std::make_pair("v", [](float const & x) { return std::abs(x) > 20; });
            //_axis[sf::Joystick::PovX] = std::make_pair("povX", [](float const & x) { return std::abs(x) > 20; });
            //_axis[sf::Joystick::PovY] = std::make_pair("povY", [](float const & x) { return std::abs(x) > 20; });
     

            _keyMapping[Button::A] = std::make_pair(_playerList.at(0), Event::A);
            _keyMapping[Button::B] = std::make_pair(_playerList.at(0), Event::B);
            _keyMapping[Button::X] = std::make_pair(_playerList.at(0), Event::X);
            _keyMapping[Button::Y] = std::make_pair(_playerList.at(0), Event::Y);
            _keyMapping[Button::LT] = std::make_pair(_playerList.at(0), Event::Trigger);
            _keyMapping[Button::RT] = std::make_pair(_playerList.at(0), Event::Trigger);
            _keyMapping[Button::Start] = std::make_pair(_playerList.at(0), Event::Ground);

            //_keyMapping[Button::A] = std::make_pair(_playerList.at(0), Event::Up);
            //_keyMapping[Button::B] = std::make_pair(_playerList.at(0), Event::Down);
            //_keyMapping[Button::X] = std::make_pair(_playerList.at(0), Event::Left);
            //_keyMapping[Button::Y] = std::make_pair(_playerList.at(0), Event::Right);



            _axisMapping[Axis::LStickUp]    = std::make_pair(_playerList.at(0), Event::Up);
            _axisMapping[Axis::LStickDown]  = std::make_pair(_playerList.at(0), Event::Down);
            _axisMapping[Axis::LStickLeft]  = std::make_pair(_playerList.at(0), Event::Left);
            _axisMapping[Axis::LStickRight] = std::make_pair(_playerList.at(0), Event::Right);
        }

        JoystickMapping::Axis
            JoystickMapping::sfAxisToAxis(sf::Joystick::Axis const & axis, float pos)
        {
            switch(axis)
            {
                case sf::Joystick::X:
                    return (pos < 0) ? Axis::LStickLeft : Axis::LStickRight;
                    break;
                case sf::Joystick::Y:
                    return (pos < 0) ? Axis::LStickUp : Axis::LStickDown;
                    break;
                default:
                    return Axis::None;
            }
        }

        sf::Joystick::Axis
            JoystickMapping::axisToSfAxis(JoystickMapping::Axis const & axis)
        {
            switch(axis)
            {
                case LStickRight: case LStickLeft: return sf::Joystick::X;
                case LStickUp: case LStickDown: return sf::Joystick::Y;
                default: return sf::Joystick::PovX;
            }
        }

        bool JoystickMapping::isInDeadZone(Axis const & axis, float pos)
        {
            switch(axis)
            {
                case LStickUp   : return (pos > -33) && (pos < 0);
                case LStickDown : return (pos <  33) && (pos > 0);
                case LStickLeft : return (pos > -33) && (pos < 0);
                case LStickRight: return (pos <  33) && (pos > 0);
                default: return false;
            }
        }


    }
}
