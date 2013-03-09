#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <graphics.h>
#include <tileset.h>

namespace Graphics
{
    class Animation : public Drawable
    {
        public:
            explicit Animation() = delete;
            explicit Animation(Tileset const &);
            explicit Animation(Animation const &) = delete;
            explicit Animation(Animation &&);
            virtual ~Animation();

        protected:
            virtual Sprite const & sprite();

        private:
            Tileset const & _tileset;
            int _currentSpriteId;
    };

}

#endif
