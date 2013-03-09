#ifndef IMAGE_H
#define IMAGE_H

#include <SFML/Graphics.hpp>
#include <graphics.h>

namespace Graphics
{
    typedef sf::Sprite Sprite;
    typedef sf::Texture Texture;

    class Image : public Drawable
    {
        public:
            Image();
            Image(Texture const &);
            Image(Image &&);
            virtual ~Image();

        protected:
            virtual Sprite const & sprite();

        private:
            Sprite * _sprite;
    };

}

#endif
