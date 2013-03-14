#include <speaker.h>

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
        _listener.reset(l);
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
        switch (e.id) { default: break; } // FIXME
    }
}
