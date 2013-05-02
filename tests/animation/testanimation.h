#ifndef TEST_ANIMATION_H_
#define TEST_ANIMATION_H_

#include <animation.h>
#include <animationparser.h>
#include <application.h>

namespace EUSDAB
{
    class AnimationTest: public Application
    {
        public:
            AnimationTest() = delete;
            AnimationTest(AnimationTest &&) = delete;
            AnimationTest(const AnimationTest &) = delete;
            AnimationTest & operator=(const AnimationTest &) = delete;

            AnimationTest(sf::RenderWindow &);
            ~AnimationTest();

        protected:
            void update();
            void event();
            void render();

        private:
            // Animation parser
            AnimationParser _animParser;

            // Animation
            Animation * _animation;
    };
}

#endif
