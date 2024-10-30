#include <functional>
#include <exceptions/LibNotAvailable.hpp>
#include <filesystem>
#include <iostream>
#include "../include/Greeter.hpp"
#include "../include/Core.hpp"

const std::array<std::string, 5> core::Core::_gameLibs = { // NOLINT(cert-err58-cpp)
    "./lib/arcade_nibbler.so",
    "./lib/arcade_pacman.so",
    "./lib/arcade_qix.so",
    "./lib/arcade_centipede.so",
    "./lib/arcade_solarfox.so"
};

const std::array<std::string, 13> core::Core::_graphicalLibs = { // NOLINT(cert-err58-cpp)
    "./lib/arcade_ncurses.so",
    "./lib/arcade_sdl2.so",
    "./lib/arcade_ndk++.so",
    "./lib/arcade_aalib.so",
    "./lib/arcade_libcaca.so",
    "./lib/arcade_allegro5.so",
    "./lib/arcade_xlib.so",
    "./lib/arcade_gtk+.so",
    "./lib/arcade_sfml.so",
    "./lib/arcade_irrlicht.so",
    "./lib/arcade_opengl.so",
    "./lib/arcade_vulkan.so",
    "./lib/arcade_qt5.so"
};

core::Core::Core(const std::string &base_lib) :
    _loop(false),
    _greeter(true),
    _gameLibIndex(0),
    _graphicalLibIndex(0)
{
    this->updateAvailableLibs();
    const auto it = std::find(
        this->_availableGraphicalLibs.begin(),
        this->_availableGraphicalLibs.end(),
        base_lib
    );
    const auto distance = std::distance(this->_availableGraphicalLibs.begin(), it);
    if (it == this->_availableGraphicalLibs.end())
        throw arcade::exceptions::LibNotAvailable(distance, this->_availableGraphicalLibs);
    this->_graphicalLibIndex = distance;
    this->_startGraphicalLibrary(this->_availableGraphicalLibs[distance]);
    this->_currentGameLib = std::make_unique<core::Greeter>(this->_availableGamesLibs);
}

void core::Core::loop()
{
    std::queue<arcade::resources::Keys> windowEvents;
    std::queue<arcade::resources::Keys> gameEvents;
    arcade::protocols::DisplayProtocol renderQueues = {{}, {}};
    arcade::Time dt;

    this->_loop = true;
    while (this->_loop) {
        core::Core::_emptyQueues(renderQueues);
        this->_currentGraphicalLib->updateTime(dt);
        this->_currentGraphicalLib->collectEvents(windowEvents);
        if (this->_greeter && dynamic_cast<core::Greeter *>(this->_currentGameLib.get())->done()) {
            this->_greeterDone();
            continue;
        }
        this->_transmitCommands(windowEvents, gameEvents);
        if (!this->_loop)
            break;
        this->_currentGameLib->tick(gameEvents, dt);
        this->_currentGameLib->prepareRendering(renderQueues);
        this->_currentGraphicalLib->render(renderQueues);
    }
}

void core::Core::updateAvailableGraphicalLibs()
{
    const auto dir = std::filesystem::directory_iterator("./lib/");

    this->_availableGraphicalLibs.clear();
    for (const auto &file : dir) {
        const auto it = std::find(
            Core::Core::_graphicalLibs.begin(),
            Core::Core::_graphicalLibs.end(),
            file.path()
        );

        if (it != Core::Core::_graphicalLibs.end())
            this->_availableGraphicalLibs.emplace_back(file.path());
    }
}

void core::Core::updateAvailableGameLibs()
{
    const auto dir = std::filesystem::directory_iterator("./lib/");

    this->_availableGamesLibs.clear();
    for (const auto &file : dir) {
        const auto it = std::find(
            Core::Core::_gameLibs.begin(),
            Core::Core::_gameLibs.end(),
            file.path()
        );

        if (it != Core::Core::_gameLibs.end())
            this->_availableGamesLibs.emplace_back(file.path());
    }
}

void core::Core::_startGraphicalLibrary(const std::string &path)
{
    auto it = this->_loaded.find(path);

    if (it == this->_loaded.end()) {
        this->_loadLibrary<interfaces::IGraphical>(path);
        it = this->_loaded.find(path);
    }
    const auto ctor = std::any_cast<std::function<interfaces::IGraphical *()>>(it->second.second);
    this->_currentGraphicalLib.reset(ctor());
}

void core::Core::_startGameLibrary(const std::string &path)
{
    auto it = this->_loaded.find(path);

    if (it == this->_loaded.end()) {
        this->_loadLibrary<interfaces::IGame>(path);
        it = this->_loaded.find(path);
    }
    const auto ctor = std::any_cast<std::function<interfaces::IGame *(std::string &)>>(it->second.second);
    this->_currentGameLib.reset(ctor(this->_username));
}

void core::Core::setGameLib(std::uint64_t lib_number)
{
    if (lib_number > core::Core::_gameLibs.size())
        throw arcade::exceptions::LibNotAvailable(lib_number, this->_availableGamesLibs);
    this->_gameLibIndex = lib_number;
    this->_startGameLibrary(this->_availableGamesLibs[lib_number]);
}

void core::Core::setGraphicalLib(std::uint64_t lib_number)
{
    if (lib_number > core::Core::_graphicalLibs.size())
        throw arcade::exceptions::LibNotAvailable(lib_number, this->_availableGraphicalLibs);
    this->_graphicalLibIndex = lib_number;
    this->_startGraphicalLibrary(this->_availableGraphicalLibs[lib_number]);

}

void core::Core::updateAvailableLibs()
{
    this->updateAvailableGraphicalLibs();
    this->updateAvailableGameLibs();
}

void core::Core::_transmitCommands(
    std::queue<arcade::resources::Keys> &windowEvents,
    std::queue<arcade::resources::Keys> &gameEvents
) {
    while (!windowEvents.empty()) {
        const auto key = windowEvents.front();

        if (key == arcade::resources::Keys::Close) {
            this->_loop = false;
            return;
        }
        if (!this->_greeter) {
            if (!this->_interceptCommand(key))
                gameEvents.push(key);
        } else
            gameEvents.push(key);
        windowEvents.pop();
    }
}

bool core::Core::_interceptCommand(arcade::resources::Keys key)
{
    switch (key) {
        case arcade::resources::Keys::G:
            this->_rotateGraphicalLibrary();
            return true;
        case arcade::resources::Keys::D:
            this->_rotateGameLibrary();
            return true;
        case arcade::resources::Keys::H:
            this->_loop = false;
            return true;
        default:
            return false;
    }
}

void core::Core::_rotateGraphicalLibrary()
{
    if (this->_graphicalLibIndex + 1 < this->_availableGraphicalLibs.size())
        this->setGraphicalLib(this->_graphicalLibIndex + 1);
    else
        this->setGraphicalLib(0);
}

void core::Core::_rotateGameLibrary()
{
    if (this->_gameLibIndex < this->_availableGamesLibs.size() - 1)
        this->setGameLib(this->_gameLibIndex + 1);
    else
        this->setGameLib(0);
}

void core::Core::_greeterDone()
{
    const auto greeter = dynamic_cast<core::Greeter *>(this->_currentGameLib.get());

    this->_greeter = false;
    this->_username = greeter->getUsername();
    this->setGameLib(greeter->getSelectedGameLibrary());
}

core::Core::~Core()
{
    this->_currentGraphicalLib.reset();
    this->_currentGameLib.reset();
}

void core::Core::_emptyQueues(arcade::protocols::DisplayProtocol &renderQueues)
{
    while (!renderQueues.sprites.empty())
        renderQueues.sprites.pop();
    while (!renderQueues.texts.empty())
        renderQueues.texts.pop();
}
