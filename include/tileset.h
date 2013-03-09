#ifndef TILESET_H_
#define TILESET_H_

#include <vector>
#include <string>
#include <map>
#include <ctime>

#include "graphics.h"
#include "hitbox.h"

namespace Graphics {
    class Tileset
    {
        public:
            explicit Tileset(std::vector<Graphics::Sprite *> lsImage, std::vector<Geometry::Hitbox *> lsHitbox, std::time_t framePerImage);
            explicit Tileset(Tileset const &) = delete;
            virtual ~Tileset();

            std::vector<Graphics::Sprite *> const & lsImage() const;
            std::vector<Geometry::Hitbox *> const & lsHitbox() const;
            std::time_t framePerImage() const;

        private:
            std::vector<Graphics::Sprite *> _lsImage;
            std::vector<Geometry::Hitbox *> _lsHitbox;
            std::time_t _framePerImage;
    };
}

#endif
