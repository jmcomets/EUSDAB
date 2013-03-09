#include <view.h>

View::View()
{
}

View::~View()
{
}


void View::attach(Observer * obs)
{
    _observers.insert(obs);
}

void View::detach(Observer * obs)
{
    _observers.erase(obs);
}

void View::update()
{
    for(auto it: _observers)
    {
        //it->update(this);
    }
}


