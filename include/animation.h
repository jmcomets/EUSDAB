#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <drawable.h>

namespace Graphics
{
    typedef sf::Sprite Sprite;
    typedef sf::Texture Texture;

class Animation : public Drawable
{
    public:
        Animation();
        Animation(std::vector<Texture *> const &);
        Animation(Animation &&);
        virtual ~Animation();

    protected:
        virtual Sprite const & sprite() const;

    private:
        std::vector<Sprite *> _sprites;
        int _currentSpriteId;

};

}

#endif
