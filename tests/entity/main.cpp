#include "testentity.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "EUSDAB");
    EUSDAB::Application * app = new EUSDAB::EntityTest(window);
    app->run();
    return 0;
}
