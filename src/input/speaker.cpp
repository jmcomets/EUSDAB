#include <input/speaker.h>
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
            if (_listener != nullptr)
            {
                //_listener->onLeave();
            }
            _listener = l;
            //_listener->onEnter();
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
                const Event & e = _events.front();
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
                        _listener->onNextFrame();
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

                    case Event::Grab:
                        _listener->onGrab(e);
                        break;

                    case Event::Collide:
                        _listener->onCollide(e);
                        break;

                    case Event::Ground:
                        _listener->onGround(e);
                        break;

                    default:
                        break;
                }
                _events.pop();
            }
        }
    }
}
