#ifndef TILESET_H_
#define TILESET_H_

#include <ctime>
#include <memory>
#include <vector>
#include <graphics.h>
#include <hitbox.h>

namespace Graphics
{
    class Tileset
    {
        public:
            template <typename IterSprites, typename IterHitboxes>
                Tileset(IterSprites spBegin, IterSprites spEnd,
                        IterHitboxes hbBegin, IterHitboxes hbEnd,
                        std::time_t framesPerImage):
                    _images(spBegin, spEnd), _hitboxes(hbBegin, hbEnd),
                    _fpi(framesPerImage) {}
            Tileset(std::time_t framesPerImage):
                _fpi(framesPerImage) {}
            Tileset(Tileset &&) = default;
            Tileset(const Tileset &) = default;
            ~Tileset() = default;
            Tileset & operator=(const Tileset &) = default;
            std::time_t framesPerImage() const;
            typedef std::shared_ptr<Sprite> SpritePtr;
            typedef std::shared_ptr<Geometry::Hitbox> HitboxPtr;
            SpritePtr spriteAt(std::size_t) const;
            HitboxPtr hitboxAt(std::size_t) const;
            std::size_t nbSprites() const;
            std::size_t nbHitboxes() const;
            void addSprite(Sprite *);
            void addHitbox(Geometry::Hitbox *);

        private:
            std::vector<SpritePtr> _images;
            std::vector<HitboxPtr> _hitboxes;
            std::time_t _fpi;
    };
}

#endif
