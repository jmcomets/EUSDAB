#include <graphics.h>

namespace Graphics
{

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


