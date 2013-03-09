#ifndef TILESET_H_
#define TILESET_H_

#include <vector>
#include <string>
#include <map>
#include <ctime>

#include "graphics.h"

class Hitbox;

namespace Graphics {
    class Tileset
    {
        public:
            explicit Tileset(std::vector<Sprite *> lsImage, std::vector<Hitbox *> lsHitbox, std::time_t framePerImage);
            explicit Tileset(Tileset const &) = delete;
            virtual ~Tileset();

            std::vector<Sprite *> const & lsImage() const;
            std::vector<Hitbox *> const & lsHitbox() const;
            std::time_t framePerImage() const;

        private:
            std::vector<Sprite *> _lsImage;
            std::vector<Hitbox *> _lsHitbox;
            std::time_t _framePerImage;
    };
}

#endif
