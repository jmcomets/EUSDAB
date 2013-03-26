#ifndef HITBOX_H_
#define HITBOX_H_

#include <initializer_list>
#include <type_traits>
#include <forward_list>
#include <physics/obb2.h>

namespace EUSDAB
{
    namespace Physics
    {
        // Encapsulates the commonly used `Hitbox` as a list of
        // oriented-bounding-boxes (or OBB).
        //
        // Currently used the `float` unit for computations,
        // accessable via the `Hitbox::Unit` member type.
        //
        // Most modifying methods return a reference to the
        // object they are applied upon to allow method chaining.
        class Hitbox
        {
            public:
                // Unit used for OBBs
                typedef float Unit;

                // Unit used for angles
                typedef float Angle;

                // Range constructor taking (begin, end) iterators
                // which verify STL's `InputIterator` concept.
                //
                // The underlying type is checked at compile-time
                // via static assertion.
                template <typename InputIt>
                    Hitbox(InputIt begin, InputIt end):
                        _obbList(begin, end)
                {
                    typedef typename InputIt::value_type V;
                    static_assert(std::is_same<OBB2<Unit>, V>::value, 
                        "Hitbox must be constructed from OBB2<Hitbox::Unit>");
                }

                // Construct from `initializer_list`, an in-place range
                Hitbox(std::initializer_list<OBB2<Unit>>);

                // Allow all defaults (no pointers here)
                Hitbox() = default;
                Hitbox(Hitbox &&) = default;
                Hitbox(const Hitbox &) = default;
                ~Hitbox() = default;
                Hitbox & operator=(const Hitbox &) = default;

                // Add an OBB to the Hitbox
                Hitbox & add(const OBB2<Unit> &);

                // Add all of another Hitbox's OBBs (copy)
                Hitbox & add(const Hitbox &);

                // Check collision with a specific OBB
                bool collides(const OBB2<Unit> &) const;

                // Check collision with another Hitbox
                bool collides(const Hitbox &) const;

                // Check if a vector is contained
                bool contains(const Vector2<Unit> &) const;

                // Rotate Hitbox -> rotate all OBBs
                Hitbox & rotate(Angle);

                // Translate Hitbox -> translate all OBBs
                Hitbox & translate(const Vector2<Unit> &);

            private:
                // Only forward iteration is needed and hitbox adding
                // should be done dynamically -> STL's `forward_list`
                std::forward_list<OBB2<Unit>> _obbList;
        };
    }
}

#endif
