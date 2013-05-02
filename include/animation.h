#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>
#include <list>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <physics/config.h>
#include <physics/hitbox.h>
#include <texturemanager.h>

namespace EUSDAB
{
    // Provided for convenience when
    // adding frames to the animation.
    class Frame
    {
        public:
            // Shortcuts
            typedef Physics::Hitbox<Physics::Unit> Hitbox;
            typedef std::vector<Hitbox> HitboxList;
            typedef Graphics::TextureManager::TexturePtr TexturePtr;

            Frame();
            Frame(Frame &&) = default;
            Frame(const Frame &) = default;
            ~Frame() = default;
            Frame & operator=(const Frame &) = default;

            Frame(const TexturePtr &);

            template <typename InputIter>
                Frame(const TexturePtr & texture, 
                        InputIter begin, InputIter end):
                    _texture(texture),
                    _hitboxList(begin, end)
            {
            }

            // Get/Set the frame texture
            void setTexture(const TexturePtr &);
            TexturePtr texture();

            // Add hitboxes to the frame
            void addHitbox(const Hitbox &);

            // Get the hitbox list
            HitboxList & hitboxList();
            // ...const version
            const HitboxList & hitboxList() const;

        private:
            TexturePtr _texture;
            HitboxList _hitboxList;
    };

    class Animation
    {
        public:
            // Shortcuts
            typedef Frame::HitboxList HitboxList;

            Animation();
            Animation(Animation &&) = default;
            Animation(const Animation &) = default;
            ~Animation() = default;

            template <typename InputIter>
                Animation(InputIter begin, InputIter end):
                    _frames(begin, end), _sprite(_frames.front()),
                    _paused(false)
            {
                // TODO assert for begin != end ?
            }

            // Add a frame to the Animation
            void addFrame(const Frame &);

            // Refresh the animation
            void refresh();

            // Advance the animation to the next Image/Hitbox
            void advance();

            // Get the current frame
            Frame & current();
            // ...const version
            const Frame & current() const;

            // Get the current sprite
            sf::Sprite & sprite();
            // ...const version
            const sf::Sprite & sprite() const;

            // Get the current hitbox
            HitboxList & hitboxList();
            // ...const version
            const HitboxList & hitboxList() const;

            // Get/Set the "paused" flag
            bool paused() const;
            void setPaused(bool = true);

        private:
            std::list<Frame> _frames;
            sf::Sprite _sprite;
            bool _paused;
    };
}

#endif
