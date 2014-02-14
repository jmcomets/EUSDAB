template <typename InputIter>
Controller::Controller(sf::RenderTarget & target,
        InputIter begin, InputIter end,
        const Physics::World * world,
        bool psyche, std::string const & rootDir):
    _target(target), _entityList(),
        _playerList(begin, end),
        _world(world),
        _lsChar(),
        _texRickHard(new sf::Texture()),
        _texCharlie(new sf::Texture()),
        _texPedroPanda(new sf::Texture()),
        _shader_rainbow(new sf::Shader()),
        _shader_filter(new sf::Shader()),
        _psyche(psyche)
{
    assert(_world != nullptr);

    _lsChar[0].loadFromFile(rootDir + "assets/hud/number_0.png");
    _lsChar[1].loadFromFile(rootDir + "assets/hud/number_1.png");
    _lsChar[2].loadFromFile(rootDir + "assets/hud/number_2.png");
    _lsChar[3].loadFromFile(rootDir + "assets/hud/number_3.png");
    _lsChar[4].loadFromFile(rootDir + "assets/hud/number_4.png");
    _lsChar[5].loadFromFile(rootDir + "assets/hud/number_5.png");
    _lsChar[6].loadFromFile(rootDir + "assets/hud/number_6.png");
    _lsChar[7].loadFromFile(rootDir + "assets/hud/number_7.png");
    _lsChar[8].loadFromFile(rootDir + "assets/hud/number_8.png");
    _lsChar[9].loadFromFile(rootDir + "assets/hud/number_9.png");
    _lsChar[10].loadFromFile(rootDir + "assets/hud/percent.png");

    _texRickHard->loadFromFile(rootDir + "assets/hud/jauge_rickhard.png");
    _texCharlie->loadFromFile(rootDir + "assets/hud/jauge_charlie.png");
    _texPedroPanda->loadFromFile(rootDir + "assets/hud/jauge_pedropanda.png");

    _shader_rainbow->loadFromFile(rootDir + "assets/shader/wave.vert", sf::Shader::Vertex);
    _shader_filter->loadFromFile(rootDir + "assets/shader/filter.vert", sf::Shader::Vertex);
}

template <typename InputIter>
inline void Controller::addEntity(InputIter begin, InputIter end)
{
    for (; begin != end ; begin++)
    {
        addEntity(*begin);
    }
}

