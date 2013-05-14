#include <animation.h>

namespace EUSDAB
{
    Frame::Frame():
        _texture(nullptr), _hitboxList()
    {
    }

    Frame::Frame(const TexturePtr & tx):
        _texture(tx), _hitboxList()
    {
    }

    void Frame::setTexture(const Frame::TexturePtr & tx)
    {
        _texture = tx;
    }

    Frame::TexturePtr Frame::texture()
    {
        return _texture;
    }

    void Frame::addHitbox(const Frame::Hitbox & hb)
    {
        _hitboxList.push_back(hb);
    }

    Frame::HitboxList & Frame::hitboxList()
    {
        return _hitboxList;
    }

    const Frame::HitboxList & Frame::hitboxList() const
    {
        return _hitboxList;
    }

    // Definition of member constant
    constexpr Animation::FPI Animation::DefaultFPI;

    Animation::Animation(Animation::FPI fpi):
        _frames(), _sprite(),
        _paused(false),
        _currentFrame(0),
        _framesPerImage(fpi),
        _imagesLeft(_framesPerImage)
    {
    }

    void Animation::advance(Animation::FPI nbFrames)
    {
        if (!_frames.empty() && _paused == false)
        {
            if (_imagesLeft <= nbFrames)
            {
                explicitAdvance(nbFrames);
            }
            else
            {
                _imagesLeft -= nbFrames;
            }
        }
    }

    void Animation::explicitAdvance(Animation::FPI nbFrames)
    {
        _imagesLeft = _framesPerImage;
        _currentFrame = (_currentFrame + nbFrames) % _frames.size();
        refresh();
    }

    void Animation::refresh()
    {
        _sprite.setTexture(*current().texture());
    }

    Frame & Animation::current()
    {
        return _frames[_currentFrame];
    }

       void Animation::addFrame(const Frame & frame)
    {
        _frames.push_back(frame);
    }

    const Frame & Animation::current() const
    {
        return _frames[_currentFrame];
    }

    sf::Sprite & Animation::sprite()
    {
        return _sprite;
    }

    const sf::Sprite & Animation::sprite() const
    {
        return _sprite;
    }

    Animation::HitboxList & Animation::hitboxList()
    {
        return current().hitboxList();
    }

    const Animation::HitboxList & Animation::hitboxList() const
    {
        return current().hitboxList();
    }

    bool Animation::paused() const
    {
        return _paused;
    }

    void Animation::setPaused(bool paused)
    {
        _paused = paused;
    }

    Animation::FPI Animation::fpi() const
    {
        return _framesPerImage;
    }

    void Animation::setFPI(Animation::FPI fpi)
    {
        assert(fpi > 0);
        _framesPerImage = fpi;
    }
    
    void Animation::reset()
    {
        _currentFrame = 0;
        _imagesLeft = _framesPerImage;
        refresh();
    }
    
    void Animation::setCurrentFrame(Animation::FrameListSize frame)
    {
        if (frame < _frames.size())
        {
            _currentFrame = frame;
        }
        else
        {
            _currentFrame = _frames.size() - 1;
        }    
    }
    
    Animation::FrameListSize Animation::currentFrame() const
    {
        return _currentFrame;
    }
}
