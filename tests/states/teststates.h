#ifndef TEST_STATES_H
#define TEST_STATES_H

#include <entity.h>
#include <entityparser.h>
#include <application.h>

namespace EUSDAB
{
    class StatesTest: public Application
    {
        public:
            StatesTest() = delete;
            StatesTest(StatesTest &&) = delete;
            StatesTest(const StatesTest &) = delete;
            StatesTest & operator=(const StatesTest &) = delete;

            StatesTest(sf::RenderWindow &);
            ~StatesTest();

        protected:
            void update();
            void event();
            void render();

        private:
            // Animation parser
            EntityParser _entityParser;

            // Animation
            Entity * _entity;
    };
}

#endif
