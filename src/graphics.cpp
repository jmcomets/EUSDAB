#include <graphics.h>

namespace Graphics
{
    Drawable::~Drawable()
    {
    }

    void Drawable::render(Target & target, RenderStates renderStates) const
    {
        target.draw(sprite(), renderStates);
    }
}


