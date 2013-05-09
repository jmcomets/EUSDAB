#ifndef INPUT_MAPPING_H_
#define INPUT_MAPPING_H_

#include <vector>
#include <SFML/Window/Event.hpp>
#include <input/speaker.h>

namespace EUSDAB
{
    namespace Input
    {
        class Mapping
        {
            public:
                Mapping(Mapping &&) = default;
                Mapping(Mapping const &) = delete;
                Mapping & operator=(Mapping const &) = delete;

                Mapping(): _playerList() { }

                template <typename InputIter>
                    Mapping(InputIter begin, InputIter end):
                        _playerList(begin, end)
                {
                }

                virtual ~Mapping() { }

                virtual void pushEvent(sf::Event const & event) = 0;
                virtual void update() = 0;
            protected:

                std::vector<Speaker *> _playerList;

        };
    }
}

#endif
