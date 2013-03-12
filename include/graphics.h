#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SFML/Graphics.hpp>

namespace Graphics
{
    typedef sf::Sprite Sprite;
    typedef sf::RenderTarget Target;
    typedef sf::RenderStates RenderStates;
    typedef sf::Texture Texture;

    class Drawable
    {
        public:
            Drawable() = default;
            Drawable(Drawable &&) = delete;
            Drawable(const Drawable &) = delete;
            virtual ~Drawable();
            Drawable & operator=(const Drawable &) = delete;
            void render(Target &, RenderStates = RenderStates::Default) const;

        protected:
            virtual const Sprite & sprite() const = 0;
    };
}

#endif
