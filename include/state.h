#ifndef STATE_H_
#define STATE_H_

#include <input/listener.h>
#include <physics/transform.h>
#include <entity.h>
#include <movement.h>
#include <animation.h>
#include <soundmanager.h>

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

            State(Movement const &, Entity * = nullptr, 
                    Animation * = nullptr,
                    Graphics::SoundManager::SoundPtr = nullptr);
            virtual ~State();


            // Helper for subclasses
            void switchState(Movement const &);
            // ...shortcut version
            void switchState(Movement::Flag const &);

            //same as switchstate without the onEnter nor on Leave
            void onChangeSide(Movement const &);
            // ...shortcut version
            void onChangeSide(Movement::Flag const &);

            // Get the state's movement
            Movement movement() const;

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

            // Get/Set the sound
            Graphics::SoundManager::SoundPtr sound() const;
            void setSound(Graphics::SoundManager::SoundPtr);

            // Get/Set the attack 
            Attack * attack() const;
            void setAttack(Attack *);

            // onNextFrame -> advance Animation
            virtual void onNextFrame();

            virtual void onDamage(Event const &);

            // onEnter -> used to reset animation at the start of a state
            //and other thing now :)
            virtual void onEnter();

            virtual void onGround(Event const &);


            virtual void onUp(Event const &);

            virtual void onDown(Event const &);


            // onAnimationEnd -> fired when animation ends
            virtual void onAnimationEnd();

            // onExitWorld -> fired when off the physical world
            virtual void onExitWorld();

        protected:
            // Movement (identification)
            Movement const _mvt;

            // State boilerplate
            Entity * _entity;

            // Animation (graphics/physics)
            Animation * _animation;

            // Sound (sound)
            Graphics::SoundManager::SoundPtr _soundBuffer;

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
