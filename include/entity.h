#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <unordered_map>
#include <movement.h>

namespace EUSDAB
{
    namespace Input
    {
        class State;
    }

    class Entity
    {
        public:
            Entity(Entity &&) = default;
            Entity(Entity const &) = delete;
            Entity & operator=(Entity const &) = delete;

            Entity();
            virtual ~Entity();

            void setState(const Movement &);
            void setState(Input::State *);

            void setName(const std::string &);

            Input::State * state() const;
            Input::State * state(const Movement &) const;

            std::string name() const;

    void addState(const Movement &, Input::State *);

        protected:
            std::string _name;
            Input::State * _current;
            std::unordered_map<Movement, Input::State *> _states;
    };
}

#endif
