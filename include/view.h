#ifndef VIEW_H_
#define VIEW_H_

#include <memory>
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
    std::shared_ptr<Graphics::Drawable> graphics;
    std::shared_ptr<Audio::Sound> sound;
};

#endif
