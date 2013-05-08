#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <ctime>
#include <cassert>
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
            typedef Physics::Hitbox Hitbox;
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
            typedef std::time_t FPI;

            // Class constants
            static constexpr FPI DefaultFPI = 1;

            Animation(Animation &&) = default;
            Animation(const Animation &) = default;
            ~Animation() = default;

            template <typename InputIter>
                Animation(InputIter begin, InputIter end,
                        FPI fpi = DefaultFPI):
                    _frames(begin, end),
                    _sprite(),
                    _paused(false),
                    _framesPerImage(fpi),
                    _imagesLeft(_framesPerImage)
            {
                assert(begin != end);
                _sprite.setTexture(*_frames.front().texture());
            }

            Animation(FPI = DefaultFPI);

            // Add a frame to the Animation
            void addFrame(const Frame &);

            // Refresh the animation
            void refresh();

            // Advance the animation to the next Image/Hitbox,
            //  takes the number of frames to advance
            void advance(std::time_t = 1);

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

            // Get/Set the "frames per image"
            FPI fpi() const;
            void setFPI(FPI = DefaultFPI);

        private:
            std::list<Frame> _frames;
            sf::Sprite _sprite;
            bool _paused;
            FPI _framesPerImage;
            FPI _imagesLeft;
    };
}

#endif
