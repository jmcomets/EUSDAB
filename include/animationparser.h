#ifndef ANIMATION_PARSER_H_
#define ANIMATION_PARSER_H_

#include <animation.h>

namespace EUSDAB
{
    class AnimationParser
    {
        public:
            AnimationParser(AnimationParser &&) = default;
            AnimationParser(const AnimationParser &) = default;
            ~AnimationParser() = default;
            AnimationParser & operator=(const AnimationParser &) = default;

            AnimationParser(const std::string &);

            // Load from Animation directory, relative to base directory
            Animation * loadAnimation(const std::string &);

            // Read from stream with Animation directory given,
            //  relative to base directory
            Animation * readAnimation(std::istream &, const std::string &);

            // Get base directory
            std::string baseDirectory() const;

        protected:
            Animation * addSharedAnimation(const std::string &,
                    const Animation &);

        private:
            std::string _baseDirectory;
            std::map<std::string, Animation> _animations;
    };
}

#endif
