#include "testinput.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "EUSDAB");
    EUSDAB::Application * app = new EUSDAB::InputTest(window);
    app->run();
    delete app;
    return 0;
}
