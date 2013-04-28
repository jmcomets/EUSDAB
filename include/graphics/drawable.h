#ifndef GRAPHICS_DRAWABLE_H_
#define GRAPHICS_DRAWABLE_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace EUSDAB
{
    namespace Graphics
    {
        class Drawable 
        {
            public:
                Drawable();
                Drawable(Drawable &&) = default;
                Drawable(const Drawable &) = default;
                virtual ~Drawable();
                Drawable & operator=(const Drawable &) = default;

                // Complete draw operation
                void draw(sf::RenderTarget &, sf::RenderStates);

                // Pre/Post render callbacks, override in concrete
                //   child classes
                virtual void preRender(sf::RenderStates &);
                virtual void postRender(sf::RenderStates &);

            protected:
                // Abstract method returning a valid sf::Drawable
                //   object which can be directly rendered, or a nullptr
                //   if nothing should be rendered.
                virtual sf::Drawable * drawable() const = 0;
        };
    }
}

#endif
