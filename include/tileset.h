#ifndef __TILESET_H__
#define __TILESET_H__

#include <vector>
#include <string>

class Sprite;
class Hitbox;

class Tileset
{
    public:
        Tileset(std::string const &);
        ~Tileset();

        std::vector<Sprite *> const & lsImage() const;
        std::vector<Hitbox *> const & lsHitbox() const;
        std::time_t framePerImage() const;

    protected:
        std::vector<Sprite *> _lsImage;
        std::vector<Hitbox *> _lsHitbox;
        time_t _framePerImage;
};

#endif

