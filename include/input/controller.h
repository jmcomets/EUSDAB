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
                Controller(const Controller &) = delete;
                ~Controller() = default;
                Controller & operator=(const Controller &) = delete;
                void addEntity(const Entity &);
                void addSpeaker(Speaker *);
                const Event & translate(const sf::Event &);
                void update();

            protected:
                std::array<Speaker *, Config::NbPlayers> _playerList;
                std::vector<Speaker *> _entityList;
                std::unordered_map<sf::EventType,
                    std::pair<Speaker * , Event::Id> _keyMapping;
        };
    }
}

#endif
