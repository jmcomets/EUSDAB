#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <graphics.h>

namespace Graphics
{
    class Image: public Drawable
    {
        public:
            Image(const Texture &);
            Image() = default;
            Image(Image &&) = default;
            Image(const Image &) = default;
            ~Image();
            Image & operator=(const Image &) = default;

        protected:
            const Sprite & sprite() const;

        private:
            std::shared_ptr<const Sprite> _sprite;
    };

}

#endif
