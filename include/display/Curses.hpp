#ifndef CURSES_HPP
#define CURSES_HPP


#include <chrono>
#include <memory>
#include <interfaces/IGraphical.hpp>
#include <resources/KeyTranslation.hpp>
#include <protocols/DisplayProtocol.hpp>
#include <misc/CursesWrapper.hpp>
#include <Common.hpp>

/*!
 * @namespace Games
 * @brief The namespace Display contains various methods and encapsulations that will be used to make the Display system work.
 */
namespace display
{
    /*!
     * @class Curses
     * @brief The Curses class is the IGraphical implementation for ncurses lib
     */
    class Curses : public interfaces::IGraphical
    {
        public:
            Curses();
            ~Curses() override;

            void render(arcade::protocols::DisplayProtocol &toRender) override;
            void collectEvents(std::queue<arcade::resources::Keys> &events) override;
            void updateTime(arcade::Time &dt) override;

        private:
            void _displaySprite(std::queue<arcade::resources::Sprite> &sprites);
            void _displayText(std::queue<arcade::resources::Text> &texts);
            std::uint16_t _getPosixColor(arcade::resources::ColorType type, arcade::resources::Color color);
            void _delayFps();

            std::chrono::time_point<std::chrono::high_resolution_clock> _lastTime;
            std::chrono::time_point<std::chrono::high_resolution_clock> _clock;
            misc::CursesWrapper _wrapper;
    };
}

#endif //CURSES_HPP
