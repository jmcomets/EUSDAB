#include "testhitbox.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "EUSDAB");
    EUSDAB::Application * app = new EUSDAB::HitboxTest(window);
    app->run();
    delete app;
    return 0;
}
