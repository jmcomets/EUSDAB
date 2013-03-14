#ifndef ENTITY_H_
#define ENTITY_H_

#include <unordered_map>
#include <SFML/System/Vector2.hpp>
#include <graphics.h>
#include <view.h>
#include <state.h>

class Entity
{
    public:
        Entity() = default;
        Entity(const sf::Vector2f &);
        Entity(Entity &&) = default;
        Entity(const Entity &) = delete;
        virtual ~Entity();
        Entity & operator=(const Entity &) = delete;
        const sf::Vector2f & position() const;
        const sf::Vector2f & position(const sf::Vector2f &);
        const sf::Vector2f & move(const sf::Vector2f &);
        virtual void update() = 0;
        virtual void render(Graphics::Target &, Graphics::RenderStates) = 0;
        void addState(State::Id, State *);
        State * state() const;
        State * state(State::Id) const;
        void setState(State *);

    protected:
        State * _current;
        std::unordered_map<State::Id, State *, std::hash<int>> _states;
        sf::Vector2f _pos;
};

#endif
