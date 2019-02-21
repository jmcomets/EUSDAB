#ifndef MAIN_APPLICATION_H_
#define MAIN_APPLICATION_H_

#include <application.h>

#include <boost/optional.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include <entity.h>
#include <graphics/controller.h>
#include <input/controller.h>
#include <physics/controller.h>

#include <SFML/Audio.hpp>

namespace EUSDAB {

typedef std::string SceneId;

class Scene
{
public:
    virtual void enter();
    virtual void leave();

    virtual boost::optional<SceneId> update();

    virtual void handleEvent(const sf::Event& event);
    virtual void renderTo(sf::RenderTarget& target);
};

class MainApplication : public Application
{
public:
    typedef std::unordered_map<SceneId, std::unique_ptr<Scene>> Scenes;

    MainApplication(sf::RenderWindow& window, Scenes scenes, SceneId initialScene);

    MainApplication(const MainApplication&) = delete;
    MainApplication& operator=(const MainApplication&) = delete;

protected:
    void update() override final;
    void renderTo(sf::RenderTarget& target) override final;
    void handleEvent(const sf::Event& e) override final;

private:
    void switchTo(const SceneId& sceneId);

private:
    Scenes _scenes;
    Scene* _currentScene;
};

class MenuScene : public Scene
{
public:

};

class GameScene : public Scene
{
    typedef std::vector<Entity*> EntityList;

public:
    GameScene(const std::string& mapName,
            Physics::Vector2 mapCenter,
            const std::string& player1,
            const std::string& player2,
            const std::string& player3,
            const std::string& player4,
            bool psyche);

    GameScene(const MainApplication&) = delete;
    GameScene& operator=(const MainApplication&) = delete;

    ~GameScene();

protected:
    void enter() override final;

    void leave() override final;

    boost::optional<SceneId> update() override final;

    void handleEvent(const sf::Event& event) override final;
    void renderTo(sf::RenderTarget& target) override final;

private:
    void loadPlayer(std::string const &, unsigned int);
    void loadMap(std::string const &);

private:
    // Initial map position
    Physics::Vector2 _initialMapPosition;

    // List of entities to control
    EntityList _entityList;
    EntityList _players;

    // Input
    Input::Controller * _input;

    // Physics
    Physics::Controller * _physics;

    // Graphics
    Graphics::Controller * _graphics;

    sf::Music _music;
};
}

#endif
