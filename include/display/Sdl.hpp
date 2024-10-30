#ifndef SDL_HPP
#define SDL_HPP

#include <memory>
#include <chrono>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <interfaces/IGraphical.hpp>
#include <resources/KeyTranslation.hpp>
#include <protocols/DisplayProtocol.hpp>
#include <Common.hpp>
#include <misc/SdlWrapper.hpp>

/*!
 * @namespace Games
 * @brief The namespace Display contains various methods and encapsulations that will be used to make the Display system work.
 */
namespace display
{
    /*!
     * @class Sdl
     * @brief The Sdl class is the IGraphical implementation for SDL2 lib
     */
    class Sdl : public interfaces::IGraphical
    {
        public:
            Sdl();
            ~Sdl() override;

            void render(arcade::protocols::DisplayProtocol &toRender) override;
            void collectEvents(std::queue<arcade::resources::Keys> &events) override;
            void updateTime(arcade::Time &dt) override;

        private:
            void _displaySprite(std::queue<arcade::resources::Sprite> &sprites);
            void _displayText(std::queue<arcade::resources::Text> &texts);
            void _delayFps();

            misc::SdlWrapper _wrapper;
            std::chrono::time_point<std::chrono::high_resolution_clock> _lastTime;
            std::chrono::time_point<std::chrono::high_resolution_clock> _clock;
    };
}

#endif //SDL_HPP
