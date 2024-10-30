#ifndef IGRAPHICAL_HPP
#define IGRAPHICAL_HPP

#include <memory>
#include <queue>
#include <protocols/DisplayProtocol.hpp>
#include <resources/Keys.hpp>
#include <Common.hpp>

/*!
 * @namespace Interfaces
 * @brief The namespace Interface contains all program interfaces. It contains interfaces like IGame, IGraphical, etc.
 */
namespace interfaces
{
    /*!
    * @interface IGraphical
    * @brief the IGraphical interface defines graphical libraries behavior
    */
    class IGraphical
    {
        public:
            virtual ~IGraphical() = default;

            /*!
             * render is a method that will be called each time the window must be refreshed
             * @param toRender
             * The toRender member refers to a DisplayProtocol filled with elements to display
             */
            virtual void render(arcade::protocols::DisplayProtocol &toRender) = 0;

            /*!
             * collectEvents is a method that will e called each time the events must be collected
             * @param events
             * The events member refers to a queue of Keys that must be filled with collected events
             */
            virtual void collectEvents(std::queue<arcade::resources::Keys> &events) = 0;

            /*!
             * updateTime is a method that will be called each time the time must be updated
             * @param dt
             * the dt parameter represents the deltatime between two functions call
             */
            virtual void updateTime(arcade::Time &dt) = 0;
    };
}

#endif //IGRAPHICAL_HPP
