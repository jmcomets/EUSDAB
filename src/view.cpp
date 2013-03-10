#include <view.h>

View::View():
    _graphics(nullptr), _sound(nullptr)
{
}

View::View(Graphics::Drawable * g, Audio::Sound * s):
    _graphics(g), _sound(s)
{
}

View::~View()
{
    //delete graphics;
    //delete sound;
}
