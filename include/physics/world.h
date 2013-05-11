#ifndef WORLD_H_
#define WORLD_H_

namespace EUSDAB
{
    namespace Physics
    {
        class World 
        {
            public:
                World() = delete;
                World(World &&) = default;
                World(const World &) = default;
                ~World() = default;
                World & operator=(const World &) = default;
        
            private:
                AABB _aabb;
        };
    }
}

#endif
