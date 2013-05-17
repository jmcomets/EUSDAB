#include <animation.h>
#include <stdexcept>
#include <SFML/Graphics/RenderTexture.hpp>

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

    Frame Frame::flipped() const
    {
        // Cannot flip invalid Frame (with nil texture)
        assert(_texture != nullptr);

        // Flip sf::Texture
        // sf::RenderTexture destTx;
        // typedef unsigned int Size;
        // sf::Vector2<Size> srcSize = _texture->getSize();
        // Size srcWidth = srcSize.x, srcHeight = srcSize.y;
        // if (destTx.create(srcSize.x, srcSize.y) == false)
        // {
        //     throw std::runtime_error("Texture couldn't be flipped");
        // }

        // sf::Sprite sprite(*_texture);
        // sprite.setTextureRect(sf::IntRect(srcWidth, 0, -srcWidth, srcHeight));
        // destTx.draw(sprite);
        // destTx.display();

        // // Flip frame hitboxes
        // Frame f(TexturePtr(new sf::Texture(destTx.getTexture())));

        // Flip sf::Texture
        sf::Image img = _texture->copyToImage();
        img.flipHorizontally();
        Frame f(TexturePtr(new sf::Texture()));
        f._texture->loadFromImage(img);

        for (const Hitbox & hb : _hitboxList)
        {
            Hitbox hbCopy;
            typedef Hitbox::AABB AABB;
            for (const AABB & aabb : hb.aabbList())
            {
                AABB aabbCopy(aabb);
                typedef AABB::Unit Unit;
                static auto negate = [] (const Unit & v)
                {
                    return v * static_cast<Unit>(-1);
                };
                aabbCopy.setX(negate(aabbCopy.x()));
                hbCopy.addAABB(aabbCopy);
            }
            f.addHitbox(hbCopy);
        }
        return f;
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
        Frame::TexturePtr txPtr = current().texture();
        if (txPtr == nullptr) { return; }

        // Explicitely convert to float when halfing
        typedef unsigned int Size;
        static auto half = [] (Size v)
        {
            return static_cast<float>(v) / static_cast<float>(2);
        };

        // Transform sprite correctly
        sf::Vector2<Size> size = txPtr->getSize();
        _sprite.setOrigin(half(size.x), half(size.y));
        _sprite.setTexture(*txPtr);
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

    Animation Animation::flipped() const
    {
        Animation a(_framesPerImage);
        for (const Frame & f : _frames)
        {
            a.addFrame(f.flipped());
        }
        return a;
    }
}
