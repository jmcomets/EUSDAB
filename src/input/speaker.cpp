#include <input/speaker.h>

namespace EUSDAB
{
    namespace Input
    {
        Event::Event(Id id, Ratio ratio):
            id(id), ratio(ratio)
        {
        }

        Speaker::Speaker():
            _listener(nullptr),
            _events()
        {
        }

        Speaker::setListener(Listener * l)
        {
            if (l != nullptr)
            {
                throw std::runtime_error("Speaker cannot switch to null Listener");
            }
            else
            {
                if (_listener != nullptr)
                {
                    _listener->onLeave();
                }
                _listener = l;
                _listener->onEnter();
            }
        }

        void Speaker::push(const Event & e)
        {
            _events.push(e);
        }

        void Speaker::pollEvents()
        {
            while (_events.empty() == false)
            {
                const Event & e = _events.top();
                switch (e.id)
                {
                    Event::Up:
                        _listener->onUp(e);
                    break;

                    Event::Down:
                        _listener->onDown(e);
                    break;

                    Event::Left:
                        _listener->onLeft(e);
                    break;

                    Event::Right:
                        _listener->onRight(e);
                    break;

                    Event::A:
                        _listener->onA(e);
                    break;

                    Event::B:
                        _listener->onB(e);
                    break;

                    Event::X:
                        _listener->onX(e);
                    break;

                    Event::Y:
                        _listener->onY(e);
                    break;

                    Event::Z:
                        _listener->onZ(e);
                    break;

                    Event::Trigger:
                        _listener->onTrigger(e);
                    break;

                    Event::NextFrame:
                        _listener->onNextFrame(e);
                    break;

                    Event::Attack:
                        _listener->onAttack(e);
                    break;

                    Event::Damage:
                        _listener->onDamage(e);
                    break;

                    Event::Enter:
                        _listener->onEnter(e);
                    break;

                    Event::Leave:
                        _listener->onLeave(e);
                    break;

                    default:
                    break;
                }
            }
        }
    }
}
