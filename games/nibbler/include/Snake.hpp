#ifndef SNAKE_HPP
#define SNAKE_HPP


#include <Common.hpp>
#include <cstdint>
#include <vector>
#include "misc/Direction.hpp"
#include "misc/Cell.hpp"

/*!
 * @namespace games
 * @brief The namespace Game contains various classes that will be used to make the games work
 */
namespace games
{
    /*!
     * @class Snake
     * @brief The snake class is the encapsulation of all the data that represents the player object, snake.
     */
    class Snake
    {
        public:
            Snake() = default;
            Snake(std::uint32_t baseSize, std::uint32_t x, std::uint32_t y);
            ~Snake() = default;

            /*!
             * The increaseSnakeLength method increases the snake's length by 1.
             */
            void increaseSnakeLength();

            /*!
             * The updateCoords method update the coordinates of the snake.
             * @param direction
             * The direction parameter refers to the direction of the snake
             */
            void updateCoords(games::Direction direction);

            /*!
             * The getCoords method get the coordinates of all of the parts of the snake.
             * @return returns a vector that contains all the coordinates of all of the parts of the snake
             */
            const std::vector<arcade::Coords<std::uint32_t>> &getCoords() const
            { return this->_coordsList; }

            /*!
             * The calcCollision method calculate if the snake is colliding.
             * @param grid
             * the grid param contains the game grid
             * @param direction
             * the direction param contains the direction of the snake
             * @return returns a vector that contains all the coordinates of all of the parts of the snake
             */
            bool calcCollision(std::vector<std::vector<games::misc::NibblerCell>> &grid, Direction direction) const;
        private:
            std::vector<arcade::Coords<std::uint32_t>> _coordsList;
    };
}

#endif //SNAKE_HPP
