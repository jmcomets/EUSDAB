#include "testPainter.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "EUSDAB");
    EUSDAB::Application * app = new EUSDAB::PainterTest(window);
    app->run();
    return 0;
}
