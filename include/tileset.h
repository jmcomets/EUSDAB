#ifndef TILESET_H_
#define TILESET_H_

#include <vector>
#include <string>

#include "graphics.h"

class Sprite;
class Hitbox;

class Tileset
{
    public:
        explicit Tileset(std::string const &);
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

#endif
