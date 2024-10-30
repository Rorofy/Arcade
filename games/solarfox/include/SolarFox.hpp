#ifndef SOLARFOX_HPP
#define SOLARFOX_HPP

#include <interfaces/IGame.hpp>

/*!
 * @namespace Games
 * @brief The namespace Games contains various classes that will be used to make the Game system work
 */
namespace games
{
    /*!
     * @class SolarFox
     * @brief The SolarFox class is the IGame implementation for SolarFox game
     */
    class SolarFox : public interfaces::IGame
    {
        public:
            SolarFox(const std::string &username);
            ~SolarFox() = default;

            void tick(std::queue<arcade::resources::Keys> &events, arcade::Time &dt) override;
            void prepareRendering(arcade::protocols::DisplayProtocol &renderQueues) const override;
        private:
            const std::string &_username;
    };
}

#endif //SOLARFOX_HPP
