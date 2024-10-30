#ifndef COMMON_HPP
#define COMMON_HPP

/*!
 * @namespace Arcade
 * @brief The Arcade namespace contains all Arcade code
 */
namespace arcade
{

    /*!
     * The FRAMERATE variable contains the update framerate
     */
    static const int FRAMERATE = 60;

    /*!
     * The WIN_WIDTH variable contains the width of the window
     */
    static const int WIN_WIDTH = 1920;
    /*!
     * The WIN_HEIGHT variable contains the height of the window
     */
    static const int WIN_HEIGHT = 1080;

    /*!
     * The TERM_WIDTH variable contains the width of the terminal window
     */
    static const int TERM_WIDTH = 174;

    /*!
     * The TERM_HEIGHT variable contains the height of the terminal window
     */
    static const int TERM_HEIGHT = 54;

    /*!
     * The EXIT_ERR variable variable is the internally agreed-upon exit code
     */
    static const int EXIT_ERR = 84;

    /*!
     * The BPP variable contains the level of color of the GUI window
     */
    static const int BPP = 32;

    /*!
     * @typedef Time
     * @brief The Time type refers to a double that will be used to calculate an element position relative to time
     */
    using Time = double;

    /*!
     * @enum InterfaceType
     * @brief The InterfaceType enum contains all interfaces name (will be used with dlsym to know which interface we are using)
     */
    enum InterfaceType
    {
        IGame,
        IGraphical
    };

    /*!
     * @struct Coords
     * @brief This structure can be used to represent 2D coordinates
     * @tparam T
     * Type T refers to storage type (double, long, int, etc)
     * @var Coords::x
     * The x var refers to x coordinate
     * @var Coords::y
     * The y var refers to y coordinate
     */
    template<typename T>
    struct Coords
    {
        T x;
        T y;
    };

    /*!
     * @struct Rect
     * @brief this struct can be used to represent a rectangle
     * @tparam T
     * Type T refers to storage type (double, long, int, etc)
     * @var Rect::x
     * The x var refers to x coordinate
     * @var Rect::y
     * The y var refers to y coordinate
     * @var Rect::w
     * The w var refers to width
     * @var Rect::h
     * The h var refers to height
     */
    template<typename T>
    struct Rect
    {
        T x;
        T y;
        T w;
        T h;
    };
}

#endif //COMMON_HPP
