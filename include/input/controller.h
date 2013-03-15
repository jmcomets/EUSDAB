#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

#include <vector>
#include <speaker.h>

namespace EUSDAB
{
    namespace Input
    {
        class Controller
        {
            public:
                Controller() = delete;
                Controller(Controller &&) = default;
                Controller(const Controller &) = delete;
                ~Controller() = default;
                Controller & operator=(const Controller &) = delete;
                void add(Speaker *);
                void dispatch(const sf::Event &);
                void update();

            protected:
                void dispatch(const sf::Event::KeyEvent &);
                void dispatch(const sf::Event::JoystickConnectEvent &);
                void dispatch(const sf::Event::JoystickButtonEvent &);
                void dispatch(const sf::Event::JoystickMoveEvent &);

            private:
                std::vector<Speaker *> _speakers;
        };
    }
}

#endif
