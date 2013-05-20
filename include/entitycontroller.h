#ifndef ENTITY_CONTROLLER_H_
#define ENTITY_CONTROLLER_H_

#include <memory>
#include <set>
#include <vector>
#include <entity.h>

namespace EUSDAB
{
    class EntityController
    {
        public:
            EntityController(EntityController &&) = delete;
            EntityController(const EntityController &) = delete;
            EntityController & operator=(const EntityController &) = delete;

            static std::vector<Entity *> getAllPlayers();
            static std::vector<Entity *> getAlivePlayers();
            static std::vector<Entity *> getNonPlayers();

            static void addPlayer(Entity * entity);

            template <typename InputIter>
                static void addPlayers(InputIter begin, InputIter end)
            {
                for(; begin != end; ++begin)
                {
                    addPlayer(*begin);
                }
            }

            static void addEntity(Entity * entity);

            template <typename InputIter>
                static void addEntities(InputIter begin, InputIter end)
            {
                for(; begin != end; ++begin)
                {
                    addEntity(*begin);
                }
            }

            ~EntityController();

        private:
            EntityController();
            static EntityController * instance();
            static std::shared_ptr<EntityController> _instance;
            std::set<Entity *> _entitiesNonPlayer;
            std::set<Entity *> _entitiesPlayer;
    };
}

#endif
