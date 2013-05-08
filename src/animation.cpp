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

    constexpr Animation::FPI Animation::DefaultFPI;

    Animation::Animation():
        _frames(), _sprite(),
        _paused(false), _framesPerImage(DefaultFPI)
    {
    }

    void Animation::advance(std::time_t nbFrames)
    {
        if (!_frames.empty() && _paused == false)
        {
            if (_imagesLeft <= nbFrames)
            {
                _imagesLeft = _framesPerImage;
                _frames.splice(_frames.end(), _frames, _frames.begin());
                refresh();
            }
            else
            {
                _imagesLeft -= nbFrames;
            }
        }
    }

    void Animation::refresh()
    {
        _sprite.setTexture(*_frames.front().texture());
    }

    Frame & Animation::current()
    {
        return _frames.front();
    }

    void Animation::addFrame(const Frame & frame)
    {
        _frames.push_back(frame);
    }

    const Frame & Animation::current() const
    {
        return _frames.front();
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
        _framesPerImage = fpi;
    }
}
