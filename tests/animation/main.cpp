#include "testanimation.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "EUSDAB");
    EUSDAB::AnimationTest app(window);
    app.run();
    return 0;
}
