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


//*******************************************************************//
//****************ANIMATION FONCTIONS AND PROCEDURES*****************//


    constexpr Animation::FPI Animation::DefaultFPI;

    Animation::Animation(Animation::FPI fpi):
        _frames(), _sprite(),
        _paused(false),
        _framesPerImage(fpi),
        _imagesLeft(_framesPerImage)
    {
    }

    bool Animation::advance(std::time_t nbFrames)
    {
        bool animationEnd=false;
        if (!_frames.empty() && _paused == false)
        {
            if (_imagesLeft <= nbFrames)
            {
                
                _imagesLeft = _framesPerImage;
                //_frames.splice(_frames.end(), _frames, _frames.begin());
                _curPosition+=nbFrames;
                if (_curposition>=_frames.size())
                {
                    _curposition!=(_frames.size()-1);
                    animationEnd=true;
                }
                refresh();
            }
            else
            {
                _imagesLeft -= nbFrames;
            }
        }
        return animationEnd;
    }

    void Animation::refresh()
    {
        _sprite.setTexture(*current().texture());
    }

    Frame & Animation::current()
    {
        return _frames[_curPosition];
    }
    
    std::list<Frame> & Animation::listFrame()
    {
        return _frames;
    }

    void Animation::addFrame(const Frame & frame)
    {
        _frames.push_back(frame);
    }

    const Frame & Animation::current() const
    {
        return _frames[_curPosition];
    }
    
    const std::list<Frame> & Animation::listFrame() const
    {
        return _frames;
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
    
    void Animation::resetAnimation()
    {
        _curPosition=0;
    }
    
    void Animation::setCurPosition(int position)
    {
        if (_curposition<_frames.size())
        {
            _curPosition=position;
        }
        else
        {
            _curposition!=(_frames.size()-1);
        }    
    }
    
    int Animation::position()
    {
        return _curPosition;
    }
}
