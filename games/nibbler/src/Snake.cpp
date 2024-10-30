#include "../include/Snake.hpp"

void games::Snake::updateCoords(games::Direction direction)
{
    for (std::size_t i = this->_coordsList.size() - 1; i > 0
    ; i--)
        this->_coordsList[i] = this->_coordsList[i - 1];

    switch (direction) {
        case TOP:
            --this->_coordsList[0].y;
            break;
        case BOTTOM:
            ++this->_coordsList[0].y;
            break;
        case LEFT:
            --this->_coordsList[0].x;
            break;
        case RIGHT:
            ++this->_coordsList[0].x;
            break;
    }
}

void games::Snake::increaseSnakeLength()
{
    this->_coordsList.push_back(this->_coordsList.back());
}

games::Snake::Snake(std::uint32_t baseSize, std::uint32_t x, std::uint32_t y) :
    _coordsList(baseSize)
{
    for (auto &e : this->_coordsList) {
        e.x = x;
        e.y = y;
    }
}

bool games::Snake::calcCollision(std::vector<std::vector<games::misc::NibblerCell>> &grid, Direction direction) const
{
    games::misc::NibblerCell cell = misc::VOID;

    switch (direction) {
        case TOP:
            cell = grid[this->_coordsList[0].y - 1][this->_coordsList[0].x];
            break;
        case BOTTOM:
            cell = grid[this->_coordsList[0].y + 1][this->_coordsList[0].x];
            break;
        case LEFT:
            cell = grid[this->_coordsList[0].y][this->_coordsList[0].x - 1];
            break;
        case RIGHT:
            cell = grid[this->_coordsList[0].y][this->_coordsList[0].x + 1];
            break;
    }
    return (cell != misc::VOID && cell != misc::FOOD);
}
