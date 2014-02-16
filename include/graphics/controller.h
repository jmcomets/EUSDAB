#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <array>
#include <cassert>
#include <set>
#include <SFML/Graphics.hpp>
#include <entity.h>
#include <physics/world.h>

namespace EUSDAB
{
    namespace Graphics
    {
        class Controller
        {
            public:
                Controller() = delete;

                Controller(Controller &&) = default;
                Controller(const Controller &) = default;
                ~Controller();
                Controller & operator=(const Controller &) = default;

                template <typename InputIter>
                Controller(sf::RenderTarget & target, InputIter begin, InputIter end,
                        const Physics::World * world, bool psyche, std::string const & rootDir);

                // Draw the Controller to its currently set target
                void draw();

                // Add an Entity to the Controller
                void addEntity(Entity * entity);

                // ...range version
                template <typename InputIter>
                void addEntity(InputIter begin, InputIter end);

                // Remove an Entity from the Controller
                void removeEntity(Entity * entity);

            private:
                struct CompareByZIndex
                {
                    bool operator()(Entity * lhs, Entity * rhs) const
                    {
                        return lhs->zIndex() < rhs->zIndex();
                    }
                };

                // Entity list
                typedef std::multiset<Entity *, CompareByZIndex> EntityList;

                // Rendering target
                sf::RenderTarget & _target;

                // List of entities
                EntityList _entityList;

                // List of players
                EntityList _playerList;

                // Physics world, used by camera
                const Physics::World * _world;

                std::array<sf::Texture, 11> _lsChar;
                sf::Texture * _texRickHard;
                sf::Texture * _texCharlie;
                sf::Texture * _texPedroPanda;
                sf::Texture * _texBotato;
                sf::Shader * _shader_rainbow;
                sf::Shader * _shader_filter;

                bool _psyche;
        };

        #include "controller.inl"
    }
}

#endif
