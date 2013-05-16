#ifndef TEST_ENTITY_H_
#define TEST_ENTITY_H_

#include <vector>
#include <application.h>
#include <input/controller.h>
#include <physics/controller.h>
#include <graphics/controller.h>
#include <entity.h>

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

            typedef std::vector<Entity *> EntityList;

        protected:
            void update();
            void render();
            void event();

        private:
            // List of entities to control
            EntityTest::EntityList _entityList;

            // Input
            Input::Controller * _input;

            // Physics
            Physics::Controller * _physics;

            // Graphics
            Graphics::Controller * _graphics;
    };
}

#endif
