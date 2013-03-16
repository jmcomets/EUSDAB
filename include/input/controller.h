#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

#include <array>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <entity.h>
#include <config.h>
#include <input/event.h>
#include <input/speaker.h>

namespace EUSDAB
{
    namespace Input
    {
        class Controller
        {
            public:
                Controller() = delete;
                Controller(Controller &&) = default;
                Controller(Controller const &) = delete;
                Controller & operator=(Controller const &) = delete;

                Controller(std::array<Entity *, Config::NbPlayers> const & players);
                ~Controller();

                void addEntity(Entity *);

                // Must be called only once per frame
                void pushEvent(std::vector<sf::Event> const &);

                void update();

            protected:
                std::array<Speaker *, Config::NbrPlayer> _playerList;
                std::vector<Speaker *> _entityList;

                // Configuration
                std::unordered_map<sf::Keyboard::Key, std::pair<Speaker * , Event::Id> > _keyMapping;
        };
    }
}

#endif
