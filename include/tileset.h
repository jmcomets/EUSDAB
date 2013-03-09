#ifndef __TILESET_H__
#define __TILESET_H__

#include <vector>
#include <string>

class Sprite;
class Hitbox;

class Tileset
{
    public:
        explicit Tileset(std::string const & filename);
        virtual ~Tileset();

        std::vector<Sprite *> const & lsImage() const;
        std::vector<Hitbox *> const & lsHitbox() const;
        time_t framePerImage() const;

    protected:
        std::vector<Sprite *> _lsImage;
        std::vector<Hitbox *> _lsHitbox;
        time_t _framePerImage;
};

#endif

