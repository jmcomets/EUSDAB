#include "testhitbox.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace EUSDAB
{
    using namespace Physics;

    HitboxTest::HitboxTest(sf::RenderWindow & window):
        Application(window),
        _hitbox1(), _hitbox2(),
        _rectList1(), _rectList2()
    {
        // Make first Hitbox
        [] (Hitbox & hitbox)
        {
            hitbox.addAABB(AABB(0, 0, 100, 100));
            hitbox.addAABB(AABB(400, 100, 100, 100));
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
        auto isKeyPressed = [] (const sf::Keyboard::Key & key)
        {
            return sf::Keyboard::isKeyPressed(key);
        };

        constexpr Unit X_SPEED = 10;
        constexpr Unit Y_SPEED = 10;

        Unit x = 0;
        Unit y = 0;
        if (isKeyPressed(sf::Keyboard::Left)) { x -= X_SPEED; }
        if (isKeyPressed(sf::Keyboard::Right)) { x += X_SPEED; }
        if (isKeyPressed(sf::Keyboard::Up)) { y -= Y_SPEED; }
        if (isKeyPressed(sf::Keyboard::Down)) { y += Y_SPEED; }
        _hitbox1.translate(x, y);
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
                RectangleList::reference rect = rectList.back();
                rect.setPosition(aabb.x(), aabb.y());
                rect.setFillColor(sf::Color::Transparent);
                rect.setOutlineColor(sf::Color::White);
                rect.setOutlineThickness(2.0f);
            }
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

        if (_hitbox1.collides(_hitbox2))
        {
            updateWhenCollision(_rectList1);
            updateWhenCollision(_rectList2);
        }
    }
}
