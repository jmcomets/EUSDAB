#include "testinput.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "EUSDAB");
    EUSDAB::InputTest app(window);
    app.run();
    return 0;
}
