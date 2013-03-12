#include <view.h>

View::View():
    graphics(nullptr), sound(nullptr)
{
}

View::View(Graphics::Drawable * g, Audio::Sound * s):
    graphics(g), sound(s)
{
}

View::~View()
{
}
