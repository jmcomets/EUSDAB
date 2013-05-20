#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <set>
#include <stdextension.h>
#include <input/speaker.h>
#include <physics/config.h>
#include <physics/transform.h>
#include <movement.h>
#include <life.h>
#include <attack.h>

namespace EUSDAB
{
    // Forward declarations
    class State;
    class Attack;

    typedef unsigned int ZIndex;

    class Entity: public Input::Speaker
    {
        public:
            Entity(Entity &&) = default;
            Entity(Entity const &) = delete;
            Entity & operator=(Entity const &) = delete;

            Entity();
            virtual ~Entity();

            // General

            // Get/Set the Entity's name
            std::string name() const;
            void setName(const std::string &);

            // Physics

            // Get the Entity's position
            const Physics::Vector2 & position() const;
            // ...non-const version
            Physics::Vector2 & position();

            // Get the Entity's physical transform
            const Physics::Transform & physics() const;
            // ...non-const version
            Physics::Transform & physics();

            void setPhysicsX(Physics::Transform const & tr);
            void setPhysicsY(Physics::Transform const & tr);

            // get if the entity is gravitable
            bool gravitable() const;
            // ...non-const version
            bool & gravitable();

            // Attack module

            // Actually attack another entity
            void attack(Entity *); // FIXME const ? 

            // State module

            // Get the Entity's state directly
            State * state() const;
            // ...or by lookup by movement
            State * state(const Movement &) const;

            // Set the Entity's state directly
            void setState(State *);
            // ...or by lookup by movement (throws an 
            //   std::runtime_error if the given ID 
            //   isn't defined by an associated state). 
            void setState(const Movement &);

            // Add a new state to the Entity, identified
            //   by its movement (throws an std::runtime_error
            //   if the state's ID is already associated to another
            //   state).
            void addState(State *);

            void setLife(Life * life);
            
            Life * life() const;

            void setZIndex(ZIndex const & zIndex);
            
            ZIndex const & zIndex() const;
            
            //return a boolean value telling if a jump is possible
            bool canJump();
            
            //les getters et les setters pr le nbr de jump et le nbr max
            typedef int NbJumps;
            NbJumps nbrJump();
            NbJumps nbrJumpMax(); 
            void setNbrJump(int);
            
            //getter et setter pour jump possible
            bool jumpPossible();
            void setJumpPossible(bool);

        private:
            // General
            std::string _name;

            // Physics : positioning and physics transform
            Physics::Transform _physics;
            bool _gravitable;

            // State
            State * _current;
            std::set<State *, std::less_ptr<State>> _states;
            
            // Life
            Life * _life;

            //Z-Index
            ZIndex _zIndex;
            
            // Infomartion for the jumps
            NbJumps _nbrJumpLeft, _nbrJumpMax;
            bool _jumpPossible;
    };
}

#endif
