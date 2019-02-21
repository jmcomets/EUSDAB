#include <main_application.h>

#include <entity.h>
#include <state.h>
#include <entityparser.h>
#include <infiniteLife.h>
#include <percentageLife.h>
#include <graphics/controller.h>
#include <input/controller.h>
#include <input/joystickmapping.h>
#include <physics/controller.h>
#include <physics/world.h>

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <thread>

#include <SFML/Audio.hpp>

static std::string const ROOT_DIR = "./";

namespace EUSDAB {

void Scene::enter()
{
}

void Scene::leave()
{
}

boost::optional<SceneId> Scene::update()
{
    return SceneId { "game" };
}

void Scene::handleEvent(const sf::Event&)
{
}

void Scene::renderTo(sf::RenderTarget&)
{
}

MainApplication::MainApplication(sf::RenderWindow& window, Scenes scenes, SceneId initialScene):
    Application(window),
    _scenes(std::move(scenes)),
    _currentScene(nullptr)
{
    switchTo(initialScene);
}

void MainApplication::handleEvent(const sf::Event& e)
{
    _currentScene->handleEvent(e);
}

void MainApplication::update()
{
    if (auto nextScene = _currentScene->update())
    {
        switchTo(*nextScene);
    }
}

void MainApplication::renderTo(sf::RenderTarget& target)
{
    _currentScene->renderTo(target);
}

void MainApplication::switchTo(const SceneId& sceneId)
{
    auto findIt = _scenes.find(sceneId);
    if (findIt == _scenes.end())
        throw std::runtime_error("Unknown scene \"" + sceneId + "\"");

    if (_currentScene)
        _currentScene->leave();
    _currentScene = findIt->second.get();
    _currentScene->enter();
}

GameScene::GameScene(const std::string& mapName, Physics::Vector2 mapCenter,
        const std::string& player1,
        const std::string& player2,
        const std::string& player3,
        const std::string& player4,
        bool psyche):
    _initialMapPosition(mapCenter)
{
    std::cout << "Map: " << mapName << std::endl;

    std::cout << "Player 1:" << player1 << std::endl;
    std::cout << "Player 2:" << player2 << std::endl;
    std::cout << "Player 3:" << player3 << std::endl;
    std::cout << "Player 4:" << player4 << std::endl;

    std::cout << ">> Loading map..." << std::endl;

    // Map
    loadMap(mapName);

    std::vector<std::thread> loaderThreads;

    // Players
    if(player1 != "none")
        loaderThreads.push_back(std::thread([this, &player1]() { loadPlayer(player1, 0); }));
    if(player2 != "none")
        loaderThreads.push_back(std::thread([this, &player2]() { loadPlayer(player2, 1); }));
    if(player3 != "none")
        loaderThreads.push_back(std::thread([this, &player3]() { loadPlayer(player3, 2); }));
    if(player4 != "none")
        loaderThreads.push_back(std::thread([this, &player4]() { loadPlayer(player4, 3); }));

    for (auto& t : loaderThreads)
    {
        t.join();
    }

    // Input
    Input::Mapping * mapping = new Input::JoystickMapping(_players.begin(), _players.end());
    _input = new Input::Controller(_entityList.begin(), _entityList.end(), mapping);

    // Physics
    using namespace Physics;
    Unit w, h, x, y;
    if(mapName == "map_bazar")
    {
        x = 700;
        y = 200;
        w = 2300;
        h = 1200;
    }
    else if (mapName == "map_bar")
    {
        x = 700;
        y = 250;
        w = 2500;
        h = 1500;
    }
    else
    {
        throw std::runtime_error("Wrong map name");
    }

    World * world = new World(AABB(x, y, w, h), Vector2(0, 0.35f));
    _physics = new Controller(*_input, world);
    _physics->addEntity(_entityList.begin(), _entityList.end());
    _physics->addPlayer(_players.begin(), _players.end());

    // Graphics
    EntityList::iterator playersBegin = _entityList.begin() + (_entityList.size() - _players.size());

    _graphics = new Graphics::Controller(playersBegin, _entityList.end(), world, psyche, ROOT_DIR);

    _graphics->addEntity(_entityList.begin(), playersBegin);

    if(psyche == false)
    {
        if (!_music.openFromFile(ROOT_DIR + "assets/audio/musics/bazar.ogg"))
            throw std::runtime_error("Map's music wasn't loaded");
    }
    else
    {
        if (!_music.openFromFile(ROOT_DIR + "assets/audio/musics/harlem.ogg"))
            throw std::runtime_error("Map's music wasn't loaded");
    }
    _music.setLoop(true);
    _music.setVolume(50);
    _music.play();
}

GameScene::~GameScene()
{
    delete _input;
    delete _physics;
    delete _graphics;
    for (Entity * e : _entityList)
    {
        delete e;
    }
}

void GameScene::loadPlayer(std::string const & name, unsigned int id)
{
    static EntityParser entityParser(ROOT_DIR + "assets/entities");

    Entity * e = entityParser.loadEntity(name, false);

    if (e == nullptr)
        throw std::runtime_error(name + " entity wasn't loaded");

    typedef unsigned int Size;
    static auto const h = [](const Size & v)
    {
        return static_cast<Physics::Unit>(v)
            / static_cast<Physics::Unit>(2);
    };

    e->position() = Physics::Vector2(h(500 + id * 500), h(0));
    e->setInitialPosition(e->position());
    e->setName(e->name());
    e->setLife(new PercentageLife(0, 999));

    _entityList.push_back(e);
    _players.push_back(e);
}

void GameScene::loadMap(std::string const & name)
{
    static EntityParser entityParser(ROOT_DIR + "assets/entities");

    Entity* map = entityParser.loadEntity(name, true);
    if (!map)
    {
        throw std::runtime_error("Map entity wasn't loaded");
    }

    // Move map to center of window to start with
    map->position() = _initialMapPosition;

    // Map is not gravitable
    map->gravitable() = false;

    //Map life
    map->setLife(new InfiniteLife());

    _entityList.push_back(map);
}

void GameScene::enter()
{
}

void GameScene::leave()
{
}

boost::optional<SceneId> GameScene::update()
{
    _input->nextFrame();
    _physics->update();
    _input->update();
    return boost::none;
}

void GameScene::handleEvent(const sf::Event& e)
{
    _input->pushEvent(e);
}

void GameScene::renderTo(sf::RenderTarget& target)
{
    _graphics->draw(target);
}

} // namespace EUSDAB

