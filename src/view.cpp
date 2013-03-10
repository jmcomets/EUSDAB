#include <view.h>

View::View():
    View(nullptr, nullptr)
{
}

View::View(Graphics::Drawable * g, Audio::Sound * s):
    graphics(g), sound(s)
{
}

View::~View()
{
    //delete graphics;
    //delete sound;
}
