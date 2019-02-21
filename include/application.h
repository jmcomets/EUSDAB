#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <SFML/Graphics/RenderWindow.hpp>

namespace EUSDAB {

// Abstract class providing basic setup for our application,
// the 3 methods `event()`, `update()` and `render()`
// should be overriden in a derived class to do the
// corresponding game logic (game loop is the `run()` method).
class Application
{
public:
    Application(sf::RenderWindow&);

    Application(const Application&) = delete;
    Application & operator=(const Application&) = delete;

    virtual ~Application();

    // Game loop
    void run();

protected:
    // 3-step game loop callbacks
    virtual void handleEvent(const sf::Event& e);
    virtual void update();
    virtual void renderTo(sf::RenderTarget& target);

private:
    void event();

    // SFML context
    sf::RenderWindow& _window;
};

} // namespace EUSDAB

#endif // APPLICATION_H_
