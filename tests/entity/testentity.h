#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H

#include <entity.h>
#include <entityparser.h>
#include <application.h>

namespace EUSDAB
{
    class EntityTest: public Application
    {
        public:
            EntityTest() = delete;
            EntityTest(EntityTest &&) = delete;
            EntityTest(const EntityTest &) = delete;
            EntityTest & operator=(const EntityTest &) = delete;

            EntityTest(sf::RenderWindow &);
            ~EntityTest();

        protected:
            void update();
            void render();

        private:
            // Entity parser
            EntityParser _entityParser;

            // Entity
            Entity * _entity;
    };
}

#endif
