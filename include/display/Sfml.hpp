#ifndef SFML_HPP
#define SFML_HPP

#include <interfaces/IGraphical.hpp>
#include <resources/KeyTranslation.hpp>
#include <protocols/DisplayProtocol.hpp>
#include <Common.hpp>

/*!
 * @namespace Games
 * @brief The namespace Display contains various methods and encapsulations that will be used to make the Display system work.
 */namespace display
{
    /*!
     * @class Sfml
     * @brief The Curses class is the IGraphical implementation for Sfml lib
     */
    class Sfml : public interfaces::IGraphical
    {
        public:
            Sfml();
            ~Sfml() override;

            void render(arcade::protocols::DisplayProtocol &toRender) override;
            void collectEvents(std::queue<arcade::resources::Keys> &events) override;
            void updateTime(arcade::Time &dt) override;

        private:
            void _displaySprite(std::queue<arcade::resources::Sprite> &sprites);
            void _displayText(std::queue<arcade::resources::Text> &texts);

            sf::RenderWindow _window;
            sf::Clock _clock;
    };
}

#endif //SFML_HPP
