#ifndef GRAPHICS
#define GRAPHICS

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics.hpp>

namespace Graphics
{
    typedef sf::Sprite Sprite;
    typedef sf::RenderTarget Target;
    typedef sf::RenderStates RenderStates;

    class Drawable
    {
        public:
            Drawable();
            virtual ~Drawable();

            void render(Graphics::Target &, Graphics::RenderStates const & = RenderStates::Default);

        protected:
            virtual Graphics::Sprite const & sprite() = 0;
    };
}

#endif
