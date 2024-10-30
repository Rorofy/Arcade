#ifndef TEXT_HPP
#define TEXT_HPP

#include <string_view>
#include <Common.hpp>

/*!
 * @namespace Resources
 * @brief The Resources namespace contains all arcade resources
 */
namespace arcade::resources
{

    /*!
     * @struct Text
     * @brief the Text struct can be used to represent a text in all modes (sfml, sdl, ncurses, opengl, etc...)
     * @var Text::coords
     * The coords member refers to coordinates on window
     * @var Text::termCoords
     * the TermCoords member refers to the coordinates inside terminal
     * @var Text::color
     * The color member refers to the color of the text
     * @var Text::text
     * The text member refers to the text content
     * @var Text::fontPath
     * The fontPath member refers to the font path (useful when in windowed mode)
     */
    struct Text
    {
        arcade::Coords<double> coords;
        arcade::Coords<int> termCoords;
        arcade::resources::Color color;
        std::string text;
        std::string fontPath;
        std::uint32_t fontSize;
    };
}

#endif //TEXT_HPP
