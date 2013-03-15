#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

#include <array>
#include <vector>

#include <SFML/Window/Event.hpp>

#include <entity.h>
#include <input/event.h>
#include <input/speaker.h>

namespace EUSDAB {
    namespace Input
    {
        class Controller
        {
            public:
                explicit Controller() = delete;
                explicit Controller(Controller const &) = delete;
                explicit Controller(Controller &&) = default;
                Controller & operator=(Controller const &) = delete;

                virtual ~Controller();

                void addEntity(::Entity const &);

                Event const & sfml2eusdab(sf::Event const &);

            protected:
                std::array<Speaker *, ::NBR_PLAYER> _player;
                std::vector<Speaker *> _entityList;

                std::unordered_map<sf::EventType, std::pair<Speaker * , Event::Id> _key_map;
        };
    }
}

#endif

