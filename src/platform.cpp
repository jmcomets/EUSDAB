#include <platform.h>

Platform::Platform()
{
}

Platform::~Platform()
{
}

const std::string & Platform::name()
{
    return _name;
}

void Platform::name(const std::string & name)
{
    _name = name;
}

const View & Platform::view()
{
    return _view;
}

