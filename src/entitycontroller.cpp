#include <entitycontroller.h>

namespace EUSDAB
{
    EntityController * EntityController::instance()
    {
        if (_instance.get() == nullptr)
        {
            _instance.reset(new EntityController());
        }
        return _instance.get();
    }
 
    std::vector<Entity *> EntityController::getAllPlayers()
    {
        EntityController * inst = instance();
        return std::vector<Entity *>(inst->_entitiesPlayer.begin(), 
            inst->_entitiesPlayer.end());
    }

    std::vector<Entity *> EntityController::getAlivePlayers()
    {
        EntityController * inst = instance();
        std::vector<Entity *> players;

        for(auto p : inst->_entitiesPlayer)
        {
            if(p->life()->isAlive())
            {
                players.emplace_back(p);
            }
        }
        return players;
    }

    std::vector<Entity *> EntityController::getNonPlayers()
    {
        EntityController * inst = instance();
        return std::vector<Entity *>(inst->_entitiesNonPlayer.begin(), 
            inst->_entitiesNonPlayer.end());
    }

    void EntityController::addPlayer(Entity * entity)
    {
        EntityController * inst = instance();
        inst->_entitiesPlayer.insert(entity);
    }
    
    void EntityController::addEntity(Entity * entity)
    {
        EntityController * inst = instance();
        inst->_entitiesNonPlayer.insert(entity);
    }

    EntityController::~EntityController()
    {
        EntityController * inst = instance();

        for(Entity * p : inst->_entitiesPlayer)
        {
            delete p;
        }

        for(Entity * e : inst->_entitiesNonPlayer)
        {
            delete e;
        }
    }
}
