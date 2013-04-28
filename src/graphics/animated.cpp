#include <graphics/animated.h>

namespace EUSDAB
{
    namespace Graphics
    {
        Animated::~Animated()
        {
            delete _sprite;
        }

        void Animated::preRender(sf::RenderStates & states)
        {
            if (_frames.size() > 1)
            {
                _frames.splice(_frames.end(), _frames, _frames.begin());
            }
        }

        sf::Drawable * Animated::drawable() const
        {
            if (_frames.empty())
            {
                return nullptr;
            }
            else
            {
                _sprite->setTextureRect(_frames.front());
                return _sprite;
            }
        }
    }
}
