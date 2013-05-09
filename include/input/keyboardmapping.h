#ifndef INPUT_KEYBOARD_MAPPING_H
#define INPUT_KEYBOARD_MAPPING_H

#include <input/mapping.h>
#include <input/event.h>
#include <map>

namespace EUSDAB
{
    namespace Input
    {
    class KeyboardMapping: public Mapping
        {
            public:
                KeyboardMapping(KeyboardMapping &&) = default;
                KeyboardMapping(KeyboardMapping const &) = delete;
                KeyboardMapping & operator=(KeyboardMapping const &) = delete;

                KeyboardMapping();

                template <typename InputIter>
                    KeyboardMapping(InputIter begin, InputIter end):
                    Mapping(begin, end), _keyMapping()
                {
                    initMappings();
                }

                virtual ~KeyboardMapping();

                virtual void pushEvent(sf::Event const & event);
                virtual void update();

            protected:
                void initMappings();

            private:
                std::map<sf::Keyboard::Key, 
                    std::pair<Speaker *, Event::Id>> _keyMapping;
        };
    }
}

#endif
