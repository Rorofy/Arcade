#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string_view>
#include <Common.hpp>
#include "Color.hpp"

/*!
 * @namespace Resources
 * @brief The Resources namespace contains all arcade resources
 */
namespace arcade::resources
{
    /*!
     * @struct Sprite
     * @brief the Sprite structure can be used to represent a sprite on the screen
     * @var Sprite::coords
     * The coords member refers to the coordinates on window
     * @var Sprite::termCoords
     * The termCoords member refers to coordinates inside terminal
     * @var Sprite::termDisplay
     * The termCoords member refers to the display mode
     * @var Sprite::termChar
     * The termchar member refers to the character to print in the terminal
     * @var Sprite::termColor
     * The termColor member refers to a colors to represent the sprite inside the terminal
     * @var Sprite::spriteArea
     * the spriteArea member refers to a rectangle of double that defines the sprite area
     * @var Sprite::spritePath
     * the spritePath member refers to the path to the sprite (useful with in windowed mode)
     */
    struct Sprite
    {
        enum TermDisplay {
            CHARACTER,
            PIXEL
        };

        arcade::Coords<double> coords;
        arcade::Coords<int> termCoords;
        Sprite::TermDisplay termDisplay;
        std::uint32_t termChar;
        arcade::resources::Color termColor;
        arcade::Rect<double> spriteArea;
        std::string spritePath;
    };
}

#endif //SPRITE_HPP
