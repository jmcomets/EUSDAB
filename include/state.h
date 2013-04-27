#ifndef INPUT_STATE_H_
#define INPUT_STATE_H_

#include <functional>
#include <movement.h>
#include <entity.h>
#include <input/listener.h>
#include <input/speaker.h>
#include <physics/hitbox.h>

namespace EUSDAB
{
    class State: public Input::Listener
    {
        public:
            // Shortcuts for subclasses
            typedef Input::Event Event;
            typedef Input::Speaker Speaker;

            State(State &&) = default;
            State(State const &) = delete;
            State & operator=(State const &) = delete;

            State(Entity * entity = nullptr,
                    Speaker * speaker = nullptr,
                    const Movement & = Movement());
            virtual ~State();

            // Helper for subclasses
            void switchState(Movement const &);

            // Movement module

            // Get/Set the state's movement
            Movement movement() const;
            void setMovement(const Movement &);

            // Compare States by Movement
            bool operator<(const State &) const;

            // Get/Set the associated Entity
            Entity * entity() const;
            void setEntity(Entity *);

            // Get/Set the associated Speaker
            Speaker * speaker() const;
            void setSpeaker(Speaker *);

            // Physics module

            // Exposed types
            typedef Physics::Hitbox<Physics::Unit> Hitbox;
            typedef std::vector<Hitbox> HitboxList;

            // Get the hitbox list
            const HitboxList & hitboxList() const;
            // ...non const version
            //HitboxList & hitboxList();

            // Add a new hitbox to the Entity
            void addHitbox(const Hitbox &);

        protected:
            // State boilerplate
            Entity * _entity;
            Speaker * _speaker;

            // Movement (identification)
            Movement _mvt;

            // View TODO
            //View _view;

            // Physics
            HitboxList _hitboxList;
    };
}


// Specialization of std::hash<EUSDAB::State>
namespace std
{
    template <>
        struct hash<EUSDAB::State>
    {
        size_t operator()(const EUSDAB::State & x) const
        {
            return hash<EUSDAB::Movement>()(x.movement());
        }
    };
}

#endif
