#include <input/speaker.h>

#include <stdexcept>

#include <input/listener.h>

namespace EUSDAB
{
    namespace Input
    {
        Speaker::Speaker(Listener * listener):
            _listener(listener),
            _events()
        {
        }

        void Speaker::setListener(Listener * l)
        {
            if (l == nullptr)
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

        void Speaker::push(Event const & e)
        {
            _events.push(e);
        }

        void Speaker::pollEvents()
        {
            if(_listener == nullptr)
            {
                return;
            }

            while (_events.empty() == false)
            {
                Event const & e = _events.front();
                _events.pop();
                switch (e.id)
                {
                    case Event::Up:
                        _listener->onUp(e);
                        break;

                    case Event::Down:
                        _listener->onDown(e);
                        break;

                    case Event::Left:
                        _listener->onLeft(e);
                        break;

                    case Event::Right:
                        _listener->onRight(e);
                        break;

                    case Event::A:
                        _listener->onA(e);
                        break;

                    case Event::B:
                        _listener->onB(e);
                        break;

                    case Event::X:
                        _listener->onX(e);
                        break;

                    case Event::Y:
                        _listener->onY(e);
                        break;

                    case Event::Z:
                        _listener->onZ(e);
                        break;

                    case Event::Trigger:
                        _listener->onTrigger(e);
                        break;

                    case Event::NextFrame:
                        _listener->onNextFrame(e);
                        break;

                    case Event::Attack:
                        _listener->onAttack(e);
                        break;

                    case Event::Damage:
                        _listener->onDamage(e);
                        break;

                    case Event::Enter:
                        _listener->onEnter();
                        break;

                    case Event::Leave:
                        _listener->onLeave();
                        break;

                    default:
                        break;
                }
            }
        }
    }
}
