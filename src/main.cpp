#include <SFML/Graphics.hpp>
#include <application.h>

// TODO : finir le jeu
int main(int argc, const char * argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "EUSDAB");
    EUSDAB::Application app(&window);
    app.run();
    return 0;
}

