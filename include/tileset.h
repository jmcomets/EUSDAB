#ifndef TILESET_H_
#define TILESET_H_

#include <vector>
#include <string>

class Sprite;
class Hitbox;

class Tileset
{
    public:
        Tileset(const std::string &);
        ~Tileset();
        std::vector<Sprite *> const & lsImage() const;
        std::vector<Hitbox *> const & lsHitbox() const;
        std::time_t framePerImage() const;

    private:
        std::vector<Sprite *> _lsImage;
        std::vector<Hitbox *> _lsHitbox;
        std::time_t _framePerImage;
};

#endif
