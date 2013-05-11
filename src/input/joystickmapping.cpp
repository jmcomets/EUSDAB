#include <input/joystickmapping.h>
#include <cassert>
#include <iostream>

namespace EUSDAB
{
    namespace Input
    {
        JoystickMapping::JoystickMapping() : Mapping(), _btnMapping()
        {
        }

        JoystickMapping::~JoystickMapping()
        {
        }

        void JoystickMapping::pushEvent(sf::Event const & e)
        {
            int id = e.joystickButton.joystickId;
            if (e.type == sf::Event::JoystickMoved)
            {
                sf::Joystick::Axis axis = e.joystickMove.axis;
                float p = sf::Joystick::getAxisPosition(e.joystickButton.joystickId, axis);
                Axis a = sfAxisToAxis(axis, p);
                auto it = _axisMapping[id].second.find(a);
                if(it != _axisMapping[id].second.end())
                {
                    if(isInDeadZone(a, p))
                    {
                        std::cout << "IS IN DEAD ZONE : " << p << std::endl;
                        Event event(it->second, Event::Full, Event::FallingEdge);
                        _axisMapping[id].first->push(event);
                    }
                    else
                    {
                        Event event(it->second, (p > 0 ? p : -p) / 100, Event::RisingEdge);
                        _axisMapping[id].first->push(event);
                    }
                }
                else if(a == Axis::None)
                {
                    std::cout << "Axis::None" << std::endl;
                }
            }
            else if(e.type == sf::Event::JoystickButtonPressed)
            {
                auto it = _btnMapping[id].second.find(e.joystickButton.button);
                if(it != _btnMapping[id].second.end())
                {
                    Event event(it->second, Event::Full, Event::RisingEdge);
                    _btnMapping[id].first->push(event);
                }
            }
            else if(e.type == sf::Event::JoystickButtonReleased)
            {
                auto it = _btnMapping[id].second.find(e.joystickButton.button);
                if(it != _btnMapping[id].second.end())
                {
                    Event event(it->second, Event::Full, Event::FallingEdge);
                    _btnMapping[id].first->push(event);
                }
            }
        }

        void JoystickMapping::update()
        {
            for(unsigned int i = 0; i < _playerList.size(); ++i)
            {
                // Handle continuous input
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
                    float pos = sf::Joystick::getAxisPosition(i,
                        axisToSfAxis(p.first));
                    if(!isInDeadZone(p.first, pos))
                    {
                        Event event(p.second, Event::Full, Event::ContinuousEdge);
                        _axisMapping[i].first->push(event);
                    }
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
     
            for(unsigned int i = 0; i < _playerList.size(); ++i)
            {
                _btnMapping.push_back(std::make_pair(_playerList.at(i), 
                        std::map<int, Event::Id>()));

                _btnMapping[i].second[Button::A] = Event::A;
                _btnMapping[i].second[Button::B] = Event::B;
                _btnMapping[i].second[Button::X] = Event::X;
                _btnMapping[i].second[Button::Y] = Event::Y;
                _btnMapping[i].second[Button::LT] = Event::Trigger;
                _btnMapping[i].second[Button::RT] = Event::Trigger;
                _btnMapping[i].second[Button::Start] = Event::Ground;


                _axisMapping.push_back(std::make_pair(_playerList.at(i), 
                        std::map<Axis, Event::Id>()));

                _axisMapping[i].second[Axis::LStickUp]    = Event::Up;
                _axisMapping[i].second[Axis::LStickDown]  = Event::Down;
                _axisMapping[i].second[Axis::LStickLeft]  = Event::Left;
                _axisMapping[i].second[Axis::LStickRight] = Event::Right;
                //_axisMapping[i].second[Axis::RStickUp]    = Event::Up;
                //_axisMapping[i].second[Axis::RStickDown]  = Event::Down;
                //_axisMapping[i].second[Axis::RStickLeft]  = Event::Left;
                //_axisMapping[i].second[Axis::RStickRight] = Event::Right;
                //_axisMapping[i].second[Axis::DPadUp]    = Event::Up;
                //_axisMapping[i].second[Axis::DPadDown]  = Event::Down;
                //_axisMapping[i].second[Axis::DPadLeft]  = Event::Left;
                //_axisMapping[i].second[Axis::DPadRight] = Event::Right;
            }
        }

        JoystickMapping::Axis
            JoystickMapping::sfAxisToAxis(sf::Joystick::Axis const & axis, float pos)
        {
            switch(axis)
            {
                case sf::Joystick::X:
                    return (pos < 0) ? Axis::LStickLeft : Axis::LStickRight;
                case sf::Joystick::Y:
                    return (pos < 0) ? Axis::LStickUp : Axis::LStickDown;
                case sf::Joystick::Z:
                    return Axis::None;
                case sf::Joystick::R:
                    return Axis::None;
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
            switch(axis)
            {
                case LStickRight: case LStickLeft: return sf::Joystick::X;
                case LStickUp   : case LStickDown: return sf::Joystick::Y;
                case RStickRight: case RStickLeft: return sf::Joystick::U;
                case RStickUp   : case RStickDown: return sf::Joystick::V;
                case DPadRight  : case DPadLeft  : return sf::Joystick::PovX;
                case DPadUp     : case DPadDown  : return sf::Joystick::PovY;
                case None       :
                default: return sf::Joystick::PovX;
            }
        }

        bool JoystickMapping::isInDeadZone(Axis const & axis, float pos)
        {
            switch(axis)
            {
                case LStickUp   :
                case LStickLeft : 
                case RStickUp   :
                case RStickLeft : return (pos > -33);
                case LStickDown :
                case LStickRight:
                case RStickDown :
                case RStickRight: return  (pos < 33);
                case DPadLeft   :
                case DPadRight  :
                case DPadUp     :
                case DPadDown   : return false;
                case None       :
                default: return true;
            }
        }


    }
}
