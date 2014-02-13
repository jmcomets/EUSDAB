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
                ~Controller() = default;
                Controller & operator=(const Controller &) = default;

                template <typename InputIter>
                    Controller(sf::RenderTarget & target,
                            InputIter begin, InputIter end,
                            const Physics::World * world,
                            bool psyche):
                        _target(target), _entityList(),
                            _playerList(begin, end),
                            _world(world),
                            _lsChar(),
                            _texRickHard(new sf::Texture()),
                            _texCharlie(new sf::Texture()),
                            _texPedroPanda(new sf::Texture()),
                            _shader_rainbow(new sf::Shader()),
                            _shader_filter(new sf::Shader()),
                            _psyche(psyche)
                {
                    assert(_world != nullptr);

                    _lsChar[0].loadFromFile("../../assets/hud/number_0.png");
                    _lsChar[1].loadFromFile("../../assets/hud/number_1.png");
                    _lsChar[2].loadFromFile("../../assets/hud/number_2.png");
                    _lsChar[3].loadFromFile("../../assets/hud/number_3.png");
                    _lsChar[4].loadFromFile("../../assets/hud/number_4.png");
                    _lsChar[5].loadFromFile("../../assets/hud/number_5.png");
                    _lsChar[6].loadFromFile("../../assets/hud/number_6.png");
                    _lsChar[7].loadFromFile("../../assets/hud/number_7.png");
                    _lsChar[8].loadFromFile("../../assets/hud/number_8.png");
                    _lsChar[9].loadFromFile("../../assets/hud/number_9.png");
                    _lsChar[10].loadFromFile("../../assets/hud/percent.png");

                    _texRickHard->loadFromFile("../../assets/hud/jauge_rickhard.png");
                    _texCharlie->loadFromFile("../../assets/hud/jauge_charlie.png");
                    _texPedroPanda->loadFromFile("../../assets/hud/jauge_pedropanda.png");

                    _shader_rainbow->loadFromFile("../../assets/shader/wave.vert", sf::Shader::Vertex);
                    _shader_filter->loadFromFile("../../assets/shader/filter.vert", sf::Shader::Vertex);
                }

                // Draw the Controller to its currently set target
                void draw();

                // Add an Entity to the Controller
                void addEntity(Entity * entity);

                // ...range version
                template <typename InputIter>
                    void addEntity(InputIter begin, InputIter end)
                    {
                        for (; begin != end ; begin++)
                        {
                            addEntity(*begin);
                        }
                    }

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
                sf::Shader * _shader_rainbow;
                sf::Shader * _shader_filter;

                bool _psyche;
        };
    }
}

#endif
