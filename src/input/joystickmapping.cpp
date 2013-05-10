#include <input/joystickmapping.h>
#include <cassert>

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
                auto it = _axisMapping.find(sfAxisToAxis(axis, p));
                if(it != _axisMapping.end())
                {
                    Event event(it->second.second, Event::Full, Event::RisingEdge);
                    it->second.first->push(event);
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
                if (isAxisMoved(0, p.first))
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
     

            //_keyMapping[Button::A] = std::make_pair(_playerList.at(0), Event::A);
            //_keyMapping[Button::B] = std::make_pair(_playerList.at(0), Event::B);
            //_keyMapping[Button::X] = std::make_pair(_playerList.at(0), Event::X);
            //_keyMapping[Button::Y] = std::make_pair(_playerList.at(0), Event::Y);

            _keyMapping[Button::A] = std::make_pair(_playerList.at(0), Event::Up);
            _keyMapping[Button::B] = std::make_pair(_playerList.at(0), Event::Down);
            _keyMapping[Button::X] = std::make_pair(_playerList.at(0), Event::Left);
            _keyMapping[Button::Y] = std::make_pair(_playerList.at(0), Event::Right);



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
                    //FIXME add a deadzone method instead of (pos > 20 || pos < -20)
                    return (pos > 20 || pos < -20) ? ((pos < 0) ?
                            Axis::LStickLeft : Axis::LStickRight) : Axis::None;
                    break;
                case sf::Joystick::Y:
                    return (pos > 20 || pos < -20) ? ((pos < 0) ?
                            Axis::LStickUp : Axis::LStickDown) : Axis::None;
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

        bool JoystickMapping::isAxisMoved(unsigned int joystick, 
            JoystickMapping::Axis const & axis)
        {
            float pos = sf::Joystick::getAxisPosition(joystick,
                axisToSfAxis(axis));
            switch(axis)
            {
                case LStickUp: return pos < -20;
                case LStickDown: return pos > 20;
                case LStickLeft: return pos < -25;
                case LStickRight: return pos > 25;
                default: return false;
            }
        }


    }
}
