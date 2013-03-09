#include <graphics.h>

using namespace Graphics

Drawable::Drawable()
{
}

Drawable::~Drawable()
{
}

void Drawable::render(Target & target, RenderStates const & renderStates)
{
    target.draw(sprite(), renderStates);
}



