#include <graphics/drawable.h>

namespace EUSDAB
{
    namespace Graphics
    {
        Drawable::~Drawable()
        {
        }

        void Drawable::draw(sf::RenderTarget & target,
                sf::RenderStates states)
        {
            preRender(states);
            sf::Drawable * d(drawable());
            if (d != nullptr)
            {
                target.draw(*d, states);
            }
            postRender(states);
        }

        void Drawable::preRender(sf::RenderStates &)
        {
        }

        void Drawable::postRender(sf::RenderStates &)
        {
        }
    }
}
