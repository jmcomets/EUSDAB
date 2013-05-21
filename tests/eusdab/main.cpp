#include "my_application.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char * argv[])
{
    if(argc != 6)
        throw std::runtime_error("Apprend à bien passer des arguments connard");

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),
            "EUSDAB", sf::Style::Close | sf::Style::Resize);
    EUSDAB::Application * app = new EUSDAB::MyApplication(window,
            std::string(argv[1]),
            std::string(argv[2]),
            std::string(argv[3]),
            std::string(argv[4]),
            std::string(argv[5]));

    app->run();
    delete app;
    return 0;
}
