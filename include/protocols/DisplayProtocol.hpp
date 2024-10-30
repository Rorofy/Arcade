#ifndef DISPLAYPROTOCOL_HPP
#define DISPLAYPROTOCOL_HPP

#include <queue>
#include <resources/Sprite.hpp>
#include <resources/Text.hpp>

/*!
 * @namespace Protocols
 * @brief The namespace Protocols contains the structures that will be used to communicate between the GFX and Core parts. It contains protocols like GameProtocol, DisplayProtocol, etc.
 */
namespace arcade::protocols
{
    /*!
    *  @struct DisplayProtocol
    *  @brief The DisplayProtocol contains all the information to show data on screen
    *  @var DisplayProtocol::sprites
    *  Member 'sprites' refers to a queue of sprites
    *  @var DisplayProtocol::texts
    *  Member 'texts' refers to a queue of texts
    */
    struct DisplayProtocol
    {
        public:
            std::queue<arcade::resources::Sprite> sprites;
            std::queue<arcade::resources::Text> texts;
    };
}

#endif //DISPLAYPROTOCOL_HPP
