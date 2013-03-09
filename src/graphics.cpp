#include <graphics.h>

namespace Graphics
{
    typedef sf::Texture Texture;

    Drawable::Drawable()
    {
    }

    Drawable::~Drawable()
    {
    }

    void Drawable::render(Target & target, RenderStates const & renderStates) const
    {
        target.draw(sprite(), renderStates);
    }

}


