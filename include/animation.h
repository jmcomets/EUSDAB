#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <ctime>
#include <cassert>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <physics/config.h>
#include <physics/hitbox.h>
#include <graphics/texturemanager.h>

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

            // Get flipped version of this Frame,
            //  flipping both texture and hitboxes
            Frame flipped() const;

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
            typedef std::vector<Frame> FrameList;
            typedef FrameList::size_type FrameListSize;

            // Class constants
            static constexpr FPI DefaultFPI = 1;

            Animation(Animation &&) = default;
            Animation(const Animation &) = default;
            ~Animation() = default;
            Animation & operator=(const Animation &) = default;

            template <typename InputIter>
                Animation(InputIter begin, InputIter end,
                        FPI fpi = DefaultFPI):
                    _frames(begin, end),
                    _sprite(),
                    _paused(false),
                    _currentFrame(0),
                    _framesPerImage(fpi),
                    _imagesLeft(_framesPerImage)
            {
                assert(begin != end);
                _sprite.setTexture(*_frames[0].texture());
            }

            Animation(FPI = DefaultFPI);

            // Get flipped (right/left) animation, flipping all frames
            Animation flipped() const;

            // Add a frame to the Animation
            void addFrame(const Frame &);

            // Refresh the animation
            void refresh();

            // Advance the animation to the next Image/Hitbox,
            //  takes the number of frames to advance, using
            //  the FPI to ponder by the speed
            void advance(FPI = 1);

            // Advance the animation to the next Image/Hitbox,
            //  takes the number of frames to advance,
            //  without pondering by the FPI
            void explicitAdvance(FPI = 1);

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

            // Reset the animation
            void reset();

            //Get/Set the current animation frame
            FrameListSize currentFrame() const;
            void setCurrentFrame(FrameListSize frame);

        private:
            // List of frames
            FrameList _frames;

            // Animation SFML drawable
            sf::Sprite _sprite;

            // Flag telling if animation is paused
            bool _paused;

            // Current animation frame
            FrameListSize _currentFrame;

            // Current FPI
            FPI _framesPerImage;

            // Countdown to next frame advance
            FPI _imagesLeft;

    };
}

#endif
