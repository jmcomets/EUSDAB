#ifndef ANIMATED_H
#define ANIMATED_H

#include <list>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <graphics/drawable.h>

namespace EUSDAB
{
    namespace Graphics
    {
        class Animated: public Drawable 
        {
            public:
                Animated() = delete;
                Animated(Animated &&) = default;
                Animated(const Animated &) = delete;
                virtual ~Animated();
                Animated & operator=(const Animated &) = delete;

                template <typename InputIter>
                    Animated(const sf::Texture & texture,
                            InputIter begin, InputIter end):
                    _sprite(new sf::Sprite(texture)), _frames(begin, end)
                {
                }

                virtual void preRender(sf::RenderStates &);

            protected:
                virtual sf::Drawable * drawable() const;

            private:
                sf::Sprite * _sprite;
                std::list<sf::IntRect> _frames;
        };
    }
}

#endif
