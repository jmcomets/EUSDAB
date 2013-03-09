#ifndef TILESET_H_
#define TILESET_H_

#include <vector>
#include <string>
#include <map>

#include "graphics.h"

namespace Graphics {
    class Tileset
    {
        public:
            explicit Tileset(std::string const &);
            explicit Tileset(Tileset const &) = delete;
            virtual ~Tileset();

            std::vector<Sprite *> const & lsImage() const;
            std::vector<Hitbox *> const & lsHitbox() const;
            std::time_t framePerImage() const;

        protected:
            typedef map<std::string, Tileset *> pool_type;

            static pool_type s_lsTileset;

        private:
            std::vector<Sprite *> _lsImage;
            std::vector<Hitbox *> _lsHitbox;
            std::time_t _framePerImage;
    };
}

#endif
