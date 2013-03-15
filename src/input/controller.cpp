#include <input/controller.h>

namespace EUSDAB
{
    namespace Input
    {
        void Controller::add(Speaker * speaker)
        {
            _speakers.push_back(speaker);
        }

        void Controller::update()
        {
            for (Speaker * s : _speakers)
            {
                s->pollEvents();
            }
        }
    }
}

