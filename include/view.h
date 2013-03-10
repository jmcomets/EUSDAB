#ifndef VIEW_H_
#define VIEW_H_

#include <sound.h>
#include <graphics.h>

struct View
{
    View();
    View(Graphics::Drawable *, Audio::Sound *);
    View(View &&) = delete;
    View(const View &) = delete;
    ~View();
    View & operator=(const View &) = delete;
    Graphics::Drawable * _graphics;
    Audio::Sound * _sound;
};

#endif
