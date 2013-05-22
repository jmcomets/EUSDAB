#include "my_application.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char * argv[])
{
    if(argc != 6 && argc != 7)
        throw std::runtime_error("Apprend à bien passer des arguments connard");

    bool psyche = false;
    if(argc == 7)
        psyche = true;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),
            "EUSDAB", sf::Style::Close | sf::Style::Resize);
    EUSDAB::Application * app = new EUSDAB::MyApplication(window,
            std::string(argv[1]),
            std::string(argv[2]),
            std::string(argv[3]),
            std::string(argv[4]),
            std::string(argv[5]),
            psyche);

    app->run();
    delete app;
    return 0;
}
