#include "teststates.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "EUSDAB");
    EUSDAB::Application * app = new EUSDAB::StatesTest(window);
    app->run();
    return 0;
}
