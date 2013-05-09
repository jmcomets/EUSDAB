#ifndef TEST_PAINTER_H_
#define TEST_PAINTER_H_

#include <entityparser.h>
#include <application.h>
#include "painter.h"

namespace EUSDAB
{
    class PainterTest: public Application
    {
        public:
            PainterTest() = delete;
            PainterTest(PainterTest &&) = delete;
            PainterTest(const PainterTest &) = delete;
            PainterTest & operator=(const PainterTest &) = delete;

            PainterTest(sf::RenderWindow &);
            ~PainterTest();

        protected:
            void update();
            void event();
            void render();

        private:
            EntityParser _entityParser;
            Graphics::Painter _painter;
            Entity * _entity;
    };
}

#endif
