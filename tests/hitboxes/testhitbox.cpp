#include "testhitbox.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>

namespace EUSDAB
{
    using namespace Physics;

    HitboxTest::HitboxTest(sf::RenderWindow & window):
        Application(window),
        _hitbox1(), _hitbox2(),
        _rectList1(), _rectList2(),
        _globalRect1(), _globalRect2()
    {
        // Make first Hitbox
        [] (Hitbox & hitbox)
        {
            hitbox.addAABB(AABB(0, 0, 100, 100));
            hitbox.addAABB(AABB(400, 100, 100, 100));
            hitbox.addAABB(AABB(500, 400, 100, 100));
        }(_hitbox1);

        // Make second Hitbox
        [] (Hitbox & hitbox)
        {
            hitbox.addAABB(AABB(20, 20, 100, 100));
            hitbox.addAABB(AABB(200, 200, 100, 100));
        }(_hitbox2);

        updateRectangles();
    }

    HitboxTest::~HitboxTest()
    {
    }

    void HitboxTest::update()
    {
        static auto Arrow_Mapping = [] (Hitbox & hitbox)
        {
            constexpr Unit Speed = 10;
            Unit x = 0;
            Unit y = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  { x -= Speed; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { x += Speed; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    { y -= Speed; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  { y += Speed; }
            hitbox.translate(x, y);
        };

        static auto ZQSD_Mapping = [] (Hitbox & hitbox)
        {
            constexpr Unit Speed = 10;
            Unit x = 0;
            Unit y = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { x -= Speed; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { x += Speed; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { y -= Speed; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { y += Speed; }
            hitbox.translate(x, y);
        };

        ZQSD_Mapping(_hitbox1);
        Arrow_Mapping(_hitbox2);
        updateRectangles();
    }

    void HitboxTest::render()
    {
        static auto drawRectList = [&] (const RectangleList & rectList)
        {
            for (auto rect : rectList)
            {
                _window.draw(rect);
            }
        };
        drawRectList(_rectList1);
        drawRectList(_rectList2);
        _window.draw(_globalRect1);
        _window.draw(_globalRect2);
    }

    void HitboxTest::updateRectangles()
    {
        static auto updateRectList = [] (RectangleList & rectList,
                const Hitbox & hitbox)
        {
            rectList.clear();
            for (const AABB & aabb : hitbox.aabbList())
            {
                rectList.emplace_back(sf::Vector2f(aabb.width(), aabb.height()));
                Rectangle & rect = rectList.back();
                rect.setOrigin(aabb.halfwidth(), aabb.halfheight());
                rect.setPosition(aabb.x(), aabb.y());
                rect.setFillColor(sf::Color::Transparent);
                rect.setOutlineColor(sf::Color::White);
                rect.setOutlineThickness(2.0f);
            }
        };

        // Setup global rectangles display
        static auto updateGlobalRect = [] (Rectangle & rect,
                const Hitbox & hitbox)
        {
            const AABB & globalRect = hitbox.globalAABB();
            rect.setOrigin(globalRect.halfwidth(), globalRect.halfheight());
            rect.setSize(sf::Vector2f(globalRect.width(), globalRect.height()));
            rect.setPosition(globalRect.x(), globalRect.y());
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Yellow);
            rect.setOutlineThickness(2.0f);
        };

        // Callback if the hitboxes are in collision
        static auto updateWhenCollision = [] (RectangleList & rectList)
        {
            for (RectangleList::reference rect : rectList)
            {
                rect.setOutlineColor(sf::Color::Red);
            }
        };

        updateRectList(_rectList1, _hitbox1);
        updateRectList(_rectList2, _hitbox2);
        updateGlobalRect(_globalRect1, _hitbox1);
        updateGlobalRect(_globalRect2, _hitbox2);

        if (_hitbox1.collides(_hitbox2))
        {
            updateWhenCollision(_rectList1);
            updateWhenCollision(_rectList2);
        }
    }
}
