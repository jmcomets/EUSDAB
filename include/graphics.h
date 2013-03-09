#ifndef GRAPHICS
#define GRAPHICS

#include <SFML/Graphics/RenderTarget.hpp>
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
            Drawable();
            virtual ~Drawable();

            void render(Graphics::Target &, Graphics::RenderStates const & = RenderStates::Default) const;

        protected:
            virtual Graphics::Sprite const & sprite() const = 0;
    };
}

#endif
