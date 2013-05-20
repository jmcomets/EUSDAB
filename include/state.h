#ifndef STATE_H_
#define STATE_H_

#include <input/listener.h>
#include <physics/transform.h>
#include <entity.h>
#include <movement.h>
#include <animation.h>

namespace EUSDAB
{
    class State: public Input::Listener
    {
        public:
            // Shortcuts for subclasses
            typedef Input::Event Event;
            typedef Physics::Transform Transform;

            State(State &&) = default;
            State(State const &) = delete;
            State & operator=(State const &) = delete;

            State(const Movement & = Movement(), Entity * = nullptr, 
                    Animation * = nullptr);
            virtual ~State();
            
            
            // Helper for subclasses
            void switchState(Movement const &);
            // ...shortcut version
            void switchState(Movement::Flag const &);
            
            //same as switchstate without the onEnter nor on Leave
            void onChangeSide(Movement const &);
            // ...shortcut version
            void onChangeSide(Movement::Flag const &);
            
            // Get/Set the state's movement
            Movement movement() const;
            void setMovement(const Movement &);

            // Get/Set the state's transformation
            Transform const & transformation() const;
            Transform & transformation();
            void setTransformation(Transform const &);

            // Compare States by Movement
            bool operator<(const State &) const;

            // Get/Set the associated Entity
            Entity * entity() const;
            void setEntity(Entity *);

            // Get/Set the animation
            Animation * animation() const;
            void setAnimation(Animation *);

            // Get/Set the attack 
            Attack * attack() const;
            void setAttack(Attack *);

            // onNextFrame -> advance Animation
            virtual void onNextFrame();

            // onEnter -> used to reset animation at the start of a state
            //and other thing now :)
            virtual void onEnter();

            // onLeave -> used when there is smth to to when leaving a state
            virtual void onLeave();

            virtual void onGround(Event const &);





            // onAnimationEnd -> fired when animation ends
            virtual void onAnimationEnd();

            // onExitWorld -> fired when off the physical world
            virtual void onExitWorld();

        protected:
            // Movement (identification)
            Movement _mvt;

            // State boilerplate
            Entity * _entity;

            // Animation (graphics/physics)
            Animation * _animation;

            // Transformation
            Transform _transform;

            //Attack
            Attack * _attack;
    };
}

// Specialization of std::hash<EUSDAB::State>

#include <functional>

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
