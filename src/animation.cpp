#include <animation.h>

namespace EUSDAB
{
    Animation::Animation():
        _frames(), _sprite()
    {
    }

    void Animation::advance()
    {
        if (!_frames.empty())
        {
            _frames.splice(_frames.begin(), 
                    _frames, _frames.end());
            _sprite.setTexture(*_frames.front().texture());
        }
    }

    Frame & Animation::current()
    {
        return _frames.front();
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

    Frame::Frame():
        _texture(nullptr), _hitboxList()
    {
    }

    void Frame::setTexture(sf::Texture * tx)
    {
        _texture.reset(tx);
    }

    sf::Texture * Frame::texture()
    {
        return _texture.get();
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
}
