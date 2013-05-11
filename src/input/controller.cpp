#include <input/controller.h>

namespace EUSDAB
{
    namespace Input
    {
        Controller::Controller():
            _allSpeakers()
        {
        }

        void Controller::update()
        {
            _mapping->update();
            for (Speaker * s : _allSpeakers)
            {
                s->pollEvents();
            }
        }

        void Controller::addSpeaker(Speaker * s)
        {
            _allSpeakers.insert(s);
        }

        void Controller::pushEvent(const sf::Event & event)
        {
            _mapping->pushEvent(event);
        }

        void Controller::pushEvent(Speaker * s, Event const & event)
        {
            addSpeaker(s);
            s->push(event);
        }

        void Controller::nextFrame()
        {
            Event event(Event::NextFrame);
            for (Speaker * s : _allSpeakers)
            {
                s->push(event);
            }
        }
    }
}

