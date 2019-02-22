#include <main_application.h>

#include <iostream>

using namespace EUSDAB;

int main(int argc, char * argv[])
{
    if (argc < 6 || argc > 7)
    {
        std::cerr << "Wrong number of arguments: ./eusdab map_name player1 player2 player3 player4 [psyche]" << std::endl;
        return EXIT_FAILURE;
    }

    bool psyche = false;
    if(argc == 7)
        psyche = true;

    const char* mapName = argv[1];
    const char* player1 = argv[2];
    const char* player2 = argv[3];
    const char* player3 = argv[4];
    const char* player4 = argv[5];

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "EUSDAB", sf::Style::Close | sf::Style::Resize);

    MainApplication::Scenes scenes;

    // startup
    std::unique_ptr<Scene> startupScene(new StartupScene());
    scenes.emplace("startup", std::move(startupScene));

    // map selection
    std::unique_ptr<Scene> mapSelectionScene(new MapSelectionScene());
    scenes.emplace("map_selection", std::move(mapSelectionScene));

    // character selection
    std::unique_ptr<Scene> characterSelectionScene(new CharacterSelectionScene());
    scenes.emplace("character_selection", std::move(characterSelectionScene));

    // game
    auto windowSize = window.getSize();
    Physics::Vector2 mapCenter(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 2.0f);
    std::unique_ptr<Scene> gameScene(new GameScene(mapName, mapCenter, player1, player2, player3, player4, psyche));
    scenes.emplace("game", std::move(gameScene));

    std::unique_ptr<Application> app(new EUSDAB::MainApplication(window, std::move(scenes), "startup"));
    app->run();

    return EXIT_SUCCESS;
}
