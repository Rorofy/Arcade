#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include <interfaces/IGame.hpp>
#include <array>
#include "misc/Cell.hpp"
#include "Snake.hpp"

/*!
 * @namespace Games
 * @brief The namespace Games contains various classes that will be used to make the Game system work
 */
namespace games
{
    /*!
     * @class Nibbler
     * @brief The Nibbler class is the IGame implementation for Nibbler game
     */
    class Nibbler : public interfaces::IGame
    {
        public:
            explicit Nibbler(const std::string &username);
            ~Nibbler() = default;

            void tick(std::queue<arcade::resources::Keys> &events, arcade::Time &dt) override;
            void prepareRendering(arcade::protocols::DisplayProtocol &renderQueues) const override;

        private:
            static std::string _loadMap(const std::string &path);
            void _parseMap(const std::string &path);
            void _genFruit();
            void _updateGrid();
            void _handleEvents(std::queue<arcade::resources::Keys> &events);
            arcade::resources::Sprite _genCellDisplay(std::uint32_t x, std::uint32_t y) const;

            std::uint32_t _gameHeight;
            std::uint32_t _gameWidth;
            std::uint32_t _score;
            std::uint32_t _fruits;
            bool _lost;
            std::vector<std::vector<games::misc::NibblerCell>> _grid;
            const std::string &_username;
            games::Snake _snake;
            games::Direction _direction;
    };
}

#endif //NIBBLER_HPP
