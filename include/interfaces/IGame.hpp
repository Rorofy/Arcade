#ifndef IGAME_HPP
#define IGAME_HPP

#include <queue>
#include <resources/Keys.hpp>
#include <Common.hpp>
#include <protocols/DisplayProtocol.hpp>

/*!
 * @namespace Interfaces
 * @brief The namespace Interface contains all program interfaces. It contains interfaces like IGame, IGraphical, etc.
 */
namespace interfaces
{
    /*!
     * @interface IGame
     * @brief the IGame intgerface defines game libraries behavior
     */
    class IGame
    {
        public:
            ~IGame() = default;

            /*!
             * tick is a method that will be called everytime the game logic must be ran
             * @param events
             * the events param refers to a queue filled with all events captured since last call
             * @param dt
             * The dt parameter represents the deltatime between two functions call
             */
            virtual void tick(std::queue<arcade::resources::Keys> &events, arcade::Time &dt) = 0;

            /*!
             * prepareRendering is a method that will be called every time the game must be rendered
             * @param renderQueues
             * renderQueues refers to a DisplayProtocol that must be filled with data to display on screen
             */
            virtual void prepareRendering(arcade::protocols::DisplayProtocol &renderQueues) const = 0;
    };
}

#endif //IGAME_HPP
