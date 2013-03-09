#ifndef VIEW_H_
#define VIEW_H_

#include <set>
#include <sound.h>
#include <graphics.h>

// TODO: define this class' interface in a seperate file
class ViewObserver {};

class View
{
    public:
        // Default constructor
        View();

        // Value constructor
        //View(const Vector &);

        // Move constructor
        View(View &&) = delete;

        // Copy constructor
        View(const View &) = delete;

        // Destructor (non virtual)
        /* virtual */ ~View();

        // Assignment operator
        View & operator=(const View &) = delete;

        // Observer typedef for encapsulation
        typedef ViewObserver Observer;

        // Add/Remove an observer
        void attach(Observer *);
        void detach(Observer *);

        // Notify observers of update
        void update();

        // View components
        Graphics::Drawable * graphics;
        //Sound::Playable * sound;

    private:
        std::set<Observer *> _observers;
};

#endif // VIEW_H_
