#include "testentity.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 480),
            "EUSDAB", sf::Style::Close);
    EUSDAB::Application * app = new EUSDAB::EntityTest(window);
    app->run();
    return 0;
}
