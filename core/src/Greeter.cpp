#include <iostream>
#include "../include/Greeter.hpp"

void core::Greeter::tick(std::queue<arcade::resources::Keys> &events, __attribute__((unused))arcade::Time &dt)
{
    while (!events.empty()) {
        const auto cur = events.front();

        switch (this->_state) {
            case USERNAME:
                this->_addKeyToUsername(cur);
                break;
            case GAME:
                this->_choseGameLibrary(cur);
                break;
            default:
                break;
        }
        events.pop();
    }
}

void core::Greeter::prepareRendering(arcade::protocols::DisplayProtocol &renderQueues) const
{
    switch (this->_state) {
        case USERNAME:
            this->_drawUsernamePrompt(renderQueues);
            break;
        case GAME:
            this->_drawGameSelection(renderQueues);
            break;
        default:
            break;
    }
}

void core::Greeter::_addKeyToUsername(const arcade::resources::Keys &cur)
{
    const auto letter = cur + 'A';

    if (cur == arcade::resources::Keys::Enter)
        this->_state = Greeter::EditState::GAME;
    else if (this->_username.length() < Greeter::MAX_USERNAME_LENGTH) {
        if (letter >= 'A' && letter <= 'Z')
                this->_username += static_cast<char>(letter);
        else if (cur == arcade::resources::Keys::Space)
                this->_username += ' ';
    }
}

void core::Greeter::_choseGameLibrary(const arcade::resources::Keys &cur)
{
    switch (cur) {
        case arcade::resources::Keys::Down:
            this->_selectedGameLibrary =
                (this->_selectedGameLibrary == 0) ? this->_availableGamesLibs.size() - 1 : this->_selectedGameLibrary - 1;
            break;
        case arcade::resources::Keys::Up:
            this->_selectedGameLibrary =
                (this->_selectedGameLibrary + 1 < this->_availableGamesLibs.size()) ? this->_selectedGameLibrary + 1 : 0;
            break;
        case arcade::resources::Keys::Enter:
            this->_state = Greeter::EditState::DONE;
            break;
        case arcade::resources::Keys::Escape:
            this->_state = Greeter::EditState::USERNAME;
            break;
        default:
            break;
    }}

core::Greeter::Greeter(const std::vector<std::string> &availableGamesLibs) :
    _selectedGameLibrary(0),
    _state(USERNAME),
    _availableGamesLibs(availableGamesLibs)
{
    std::cout << "Initializing Greeter..." << std::endl;
}

void core::Greeter::_drawUsernamePrompt(arcade::protocols::DisplayProtocol &renderQueues) const
{
    core::Greeter::_drawBackground(renderQueues);
    renderQueues.texts.push({
        .coords = {(arcade::WIN_WIDTH / 2.0f) - 100, arcade::WIN_HEIGHT / 2.0f},
        .termCoords = {arcade::TERM_WIDTH / 2, arcade::TERM_HEIGHT / 2},
        .color = {0, 255, 0, 255},
        .text = "> " + this->_username + "_",
        .fontPath = "./fonts/FredokaOne-Regular.ttf",
        .fontSize = 20,
    });
}

void core::Greeter::_drawGameSelection(arcade::protocols::DisplayProtocol &renderQueues) const
{
    core::Greeter::_drawBackground(renderQueues);
    renderQueues.texts.push({
        .coords = {(arcade::WIN_WIDTH / 2.0f) - 185, (arcade::WIN_HEIGHT / 2.0f) - 200},
        .termCoords = {arcade::TERM_WIDTH / 2, arcade::TERM_HEIGHT / 2},
        .color = {255, 255, 255, 255},
        .text = "Chose your game",
        .fontPath = "./fonts/FredokaOne-Regular.ttf",
        .fontSize = 40
    });
    for (std::uint32_t i = 0; i < this->_availableGamesLibs.size(); i++) {
        arcade::resources::Color color = {255, 255, 255, 255};

        if (i == this->_selectedGameLibrary)
            color = {0, 255, 0, 255};
        renderQueues.texts.push({
            .coords = {(arcade::WIN_WIDTH / 2.0f) - 150, static_cast<double>((i + 1) * 50) + (arcade::WIN_HEIGHT / 2.0f)},
            .termCoords = {arcade::TERM_WIDTH / 2, static_cast<int>(i + 1) + (arcade::TERM_HEIGHT / 2)},
            .color = color,
            .text = this->_availableGamesLibs[i],
            .fontPath = "./fonts/FredokaOne-Regular.ttf",
            .fontSize = 20
        });
    }
}

void core::Greeter::_drawBackground(arcade::protocols::DisplayProtocol &renderQueues)
{
    renderQueues.sprites.push({
        {0, 0},
        {0, 0},
        arcade::resources::Sprite::TermDisplay::PIXEL,
        ' ',
        {0, 0, 0, 0},
        {0, 0, arcade::WIN_WIDTH, arcade::WIN_HEIGHT},
        "./image/greeterBackground.png"
    });
}
