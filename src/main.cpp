#include <application.h>

int main(int argc, const char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "EUSDAB");
    EUSDAB::Application app(&window);
    app.run();
    return 0;
}
