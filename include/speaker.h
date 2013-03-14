#ifndef SPEAKER_H_
#define SPEAKER_H_

#include <queue>
#include <memory>
#include <event.h>
#include <listener.h>

// Speaker class (design pattern `opinion`)
//
// Dispatches different Events to Listeners,
// simulates a state-based event handling.
class Speaker
{
    public:
        Speaker();
        Speaker(Speaker &&) = delete;
        Speaker(const Speaker &) = delete;
        ~Speaker();
        Speaker & operator=(const Speaker &) = delete;
        void setListener(Listener *);
        void push(const Event &);
        void pollEvents();

    private:
        std::shared_ptr<Listener> _listener;
        std::queue<Event> _events;
};

#endif
