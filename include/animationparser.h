#ifndef ANIMATION_PARSER_H_
#define ANIMATION_PARSER_H_

#include <animation.h>

namespace EUSDAB
{
    class AnimationParser
    {
        public:
            AnimationParser() = default;
            AnimationParser(AnimationParser &&) = default;
            AnimationParser(const AnimationParser &) = default;
            ~AnimationParser() = default;
            AnimationParser & operator=(const AnimationParser &) = default;

            // Load from Animation directory
            Animation * loadAnimation(const std::string &) const;

            // Read from stream with Animation directory given
            Animation * readAnimation(std::istream &, const std::string &) const;
    };
}

#endif
