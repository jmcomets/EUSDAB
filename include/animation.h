#ifndef ANIMATION_H
#define ANIMATION_H

#include <graphics.h>
#include <tileset.h>

namespace Graphics
{
    class Animation: public Drawable
    {
        public:
            Animation(const Tileset &);
            Animation() = delete;
            Animation(Animation &&) = delete;
            Animation(const Animation &) = delete;
            ~Animation();
            Animation & operator=(const Animation &) = delete;
            void nextFrame();

        protected:
            Sprite const & sprite() const;

        private:
            const Tileset & _tileset;
            std::size_t _index;
    };

}

#endif
