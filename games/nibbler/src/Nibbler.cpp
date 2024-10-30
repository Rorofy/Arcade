#include <fstream>
#include <iostream>
#include "../include/Nibbler.hpp"

games::Nibbler::Nibbler(const std::string &username) :
    _score(0),
    _fruits(0),
    _lost(false),
    _username(username),
    _direction(RIGHT)
{
    this->_parseMap("./map.nibbler");
    for (std::uint32_t y = 0; y < this->_grid.size(); y++)
        for (std::uint32_t x = 0; x < this->_grid[y].size(); x++)
            if (this->_grid[y][x] == misc::VOID) {
                this->_snake = games::Snake(4, x, y);
                return;
            }
}

void games::Nibbler::tick(
    __attribute__((unused))std::queue<arcade::resources::Keys> &events,
    __attribute__((unused))arcade::Time &dt
)
{
    static arcade::Time time = dt;

    if (_lost)
        return;
    time += dt;
    this->_handleEvents(events);
    if (time >= 0.1) {
        this->_updateGrid();
        time = 0;
        this->_snake.updateCoords(this->_direction);
    }
    if (this->_fruits == 0)
        this->_genFruit();
}

void games::Nibbler::prepareRendering(
    __attribute__((unused))arcade::protocols::DisplayProtocol &renderQueues
) const
{
    renderQueues.texts.push({
        .coords = {0.0f, 0.0f},
        .termCoords = {0, 0},
        .color = {255, 255, 255, 255},
        .text = "Score: " + std::to_string(this->_score),
        .fontPath = "./fonts/FredokaOne-Regular.ttf",
        .fontSize = 25
    });
    for (std::uint32_t y = 0; y < this->_grid.size(); y++)
        for (std::uint32_t x = 0; x < this->_grid[y].size(); x++)
            renderQueues.sprites.push(this->_genCellDisplay(x, y));
    if (this->_lost)
        renderQueues.texts.push({
            .coords = {arcade::WIN_WIDTH / 2.0f - 200, arcade::WIN_HEIGHT / 2.0f},
            .termCoords = {arcade::TERM_WIDTH / 2, arcade::TERM_HEIGHT / 2},
            .color = {255, 255, 255, 255},
            .text = "Game Over",
            .fontPath = "./fonts/FredokaOne-Regular.ttf",
            .fontSize = 70
        });
}

void games::Nibbler::_parseMap(const std::string &path)
{
    const auto map = games::Nibbler::_loadMap(path);
    std::size_t x = 0, y = 0;

    this->_gameHeight = std::count(map.begin(), map.end(), '\n') + 1;
    this->_gameWidth = map.find_first_of('\n');
    this->_grid = std::vector<std::vector<games::misc::NibblerCell>>(this->_gameHeight);
    for (auto &c : this->_grid)
        c = std::vector<games::misc::NibblerCell>(this->_gameWidth);
    for (const auto &c : map)
        if (c == '\n') {
            ++y;
            x = 0;
        } else
            this->_grid[y][x++] = (c == '#') ? games::misc::NibblerCell::WALL : games::misc::NibblerCell::VOID;
}

std::string games::Nibbler::_loadMap(const std::string &path)
{
    std::ifstream t(path);
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);
    str.assign(
        std::istreambuf_iterator<char>(t),
        std::istreambuf_iterator<char>()
    );
    return (str);
}

arcade::resources::Sprite games::Nibbler::_genCellDisplay(std::uint32_t x, std::uint32_t y) const
{
    arcade::resources::Sprite res = {
        .coords = {x * 64.0f, y * 64.0f},
        .termCoords = {static_cast<int>(x), static_cast<int>(y)},
        .termDisplay = arcade::resources::Sprite::PIXEL,
        .termChar = ' ',
        .termColor = {0, 0, 0, 0},
        .spriteArea = {0, 0, arcade::WIN_WIDTH, arcade::WIN_HEIGHT}
    };

    switch (this->_grid[y][x]) {
        case misc::VOID:
            res.spritePath = "./image/grass.png";
            res.termColor = {0, 0, 0, 0};
            break;
        case misc::FOOD:
            res.spritePath = "./image/food.png";
            res.termColor = {255, 0, 255, 0};
            break;
        case misc::WALL:
            res.spritePath = "./image/wall.png";
            res.termColor = {255, 255, 255, 0};
            break;
        case misc::HEAD:
            res.spritePath = "./image/head.png";
            res.termColor = {122, 255, 0, 0};
            break;
        case misc::BODY:
            res.spritePath = "./image/body.png";
            res.termColor = {0, 255, 0, 0};
            break;
    }
    return (res);
}

void games::Nibbler::_genFruit()
{
    uint32_t x = std::rand() % this->_gameWidth,
        y = std::rand() % this->_gameHeight;

    while (this->_grid[y][x] != games::misc::NibblerCell::VOID) {
        x++;

        if (x == this->_gameWidth) {
            x = 0;
            y++;
        }
        if (y == this->_gameHeight)
            return;
    }
    this->_grid[y][x] = games::misc::NibblerCell::FOOD;
    this->_fruits++;
}

void games::Nibbler::_updateGrid()
{
    static std::vector<arcade::Coords<std::uint32_t>> res(0);

    for (auto &re : res)
        this->_grid[re.y][re.x] = misc::VOID;
    res = this->_snake.getCoords();
    if (this->_grid[res[0].y][res[0].x] == misc::FOOD) {
        --this->_fruits;
        this->_score++;
        this->_snake.increaseSnakeLength();
    }
    if (this->_snake.calcCollision(this->_grid, this->_direction))
        this->_lost = true;
    for (std::uint32_t i = 0; i < res.size(); ++i)
        if (i == 0)
            this->_grid[res[i].y][res[i].x] = misc::HEAD;
        else
            this->_grid[res[i].y][res[i].x] = misc::BODY;
}

void games::Nibbler::_handleEvents(std::queue<arcade::resources::Keys> &events)
{
    while (!events.empty()) {
        const auto cur = events.front();

        switch (cur) {
            case arcade::resources::Left:
                if (this->_direction != RIGHT)
                    this->_direction = LEFT;
                break;
            case arcade::resources::Right:
                if (this->_direction != LEFT)
                    this->_direction = RIGHT;
                break;
            case arcade::resources::Up:
                if (this->_direction != BOTTOM)
                    this->_direction = TOP;
                break;
            case arcade::resources::Down:
                if (this->_direction != TOP)
                    this->_direction = BOTTOM;
                break;
            default:
                break;
        }
        events.pop();
    }
}
