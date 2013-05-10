#include "testPainter.h"
#include <stdexcept>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <texturemanager.h>
#include <movement.h>
#include <state.h>
#include <input/event.h>

namespace EUSDAB
{
    PainterTest::PainterTest(sf::RenderWindow & window):
        Application(window), _entityParser(), _painter(window)
    {
        _entity = _entityParser.loadEntity("../../assets/entities/rickhard");
        if (_entity == nullptr)
        {
            throw std::runtime_error("Entity wasn't loaded");
        }
        std::cout << "Loaded Entity " << _entity->name() << std::endl;
        _painter.addEntity(_entity);

        auto setupAnimation = [] (Animation * a)
        {
            std::cout << "Setting up animation :" << std::endl;
            constexpr float sX = 50, sY = 50;
            std::cout << "- moving sprite to (" << sX << ", " 
                << sY << ")" << std::endl;
            a->sprite().setPosition(sX, sY);
            std::cout << "Animation FPI = " << a->fpi() << std::endl;
        };
        setupAnimation(_entity->state()->animation());
    }

    PainterTest::~PainterTest()
    {
        delete _entity;
    }

    void PainterTest::event()
    {
        sf::Event e;
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::A)
                {
                    std::cout << "Adding entity "
                        << _entity->name() << std::endl;
                    _painter.addEntity(_entity);
                }
                else if (e.key.code == sf::Keyboard::R)
                {
                    std::cout << "Removing entity "
                        << _entity->name() << std::endl;
                    _painter.removeEntity(_entity);
                }
                else if (e.key.code == sf::Keyboard::P)
                {
                    Animation * a = _entity->state()->animation();
                    a->setPaused(1 - a->paused());
                    std::cout << "Toggling animation pause" << std::endl;
                }
                else if (e.key.code == sf::Keyboard::Right)
                {
                    Input::Event event(Input::Event::Right, Input::Event::Full, Input::Event::RisingEdge);
                    _entity->state()->onRight(event);
                }
                else if (e.key.code == sf::Keyboard::Left)
                {
                    Input::Event event(Input::Event::Left, Input::Event::Full, Input::Event::RisingEdge);
                    _entity->state()->onLeft(event);
                }
                else if (e.key.code == sf::Keyboard::Down)
                {
                    Input::Event event(Input::Event::Down, Input::Event::Full, Input::Event::RisingEdge);
                    _entity->state()->onDown(event);
                }
                else if (e.key.code == sf::Keyboard::Space)
                {
                    Input::Event event(Input::Event::Up, Input::Event::Full, Input::Event::RisingEdge);
                    _entity->state()->onUp(event);
                }
                else if (e.key.code == sf::Keyboard::G)
                {
                    Input::Event event(Input::Event::Ground, Input::Event::Full, Input::Event::RisingEdge);
                    _entity->state()->onGround(event);
                }
            }
            else if (e.type == sf::Event::KeyReleased)
            {
                if (e.key.code == sf::Keyboard::D)
                {
                    Input::Event event(Input::Event::Right, Input::Event::Full, Input::Event::FallingEdge);
                    _entity->state()->onRight(event);
                }
                else if (e.key.code == sf::Keyboard::Q)
                {
                    Input::Event event(Input::Event::Left, Input::Event::Full, Input::Event::FallingEdge);
                    _entity->state()->onLeft(event);
                }
                else if (e.key.code == sf::Keyboard::Z)
                {
                    Input::Event event(Input::Event::Up, Input::Event::Full, Input::Event::FallingEdge);
                    _entity->state()->onUp(event);
                }
                else if (e.key.code == sf::Keyboard::S)
                {
                    Input::Event event(Input::Event::Down, Input::Event::Full, Input::Event::FallingEdge);
                    _entity->state()->onDown(event);
                }


            }
        }
    }

    void PainterTest::update()
    {
        _entity->state()->onNextFrame();
    }

    void PainterTest::render()
    {
        _painter.draw();
    }
}
