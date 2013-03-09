#include <platform.h>

Platform::Platform()
{
}

string const & Platform::name()
{
    return _name;
}

void Platform::name(string const & name)
{
    _name = name;
}

View Platform::view()
{
    return _view;
}

