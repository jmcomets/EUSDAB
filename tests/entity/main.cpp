#include "testentity.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),
            "EUSDAB", sf::Style::Close | sf::Style::Resize);
    EUSDAB::Application * app = new EUSDAB::EntityTest(window);
    app->run();
    return 0;
}
