#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>
#include <string>

/*!
 * @namespace Resources
 * @brief The Resources namespace contains all arcade resources
 */
namespace arcade::resources
{
    /*!
     * @enum ColorType
     * @brief The ColorType enum allow you to chose the color type you wanna use
     */
    enum ColorType {
        BACKGROUND,
        FOREGROUND
    };

    /*!
     * @class Color
     * @brief The color class allows you to interact with colors
     */
    class Color
    {
        public:
            Color(std::uint8_t red = 255, std::uint8_t green = 255, std::uint8_t blue = 255, std::uint8_t opacity = 255);

            /*!
             * red value setter
             * @param val
             * The val parameter refers to new value
             */
            void setRed(std::uint8_t val)
            { this->_r = val; }

            /*!
             * green value setter
             * @param val
             * The val parameter refers to new value
             */
            void setGreen(std::uint8_t val)
            { this->_g = val; }

            /*!
             * blue value setter
             * @param val
             * The val parameter refers to new value
             */
            void setBlue(std::uint8_t val)
            { this->_b = val; }

            /*!
             * opacity value setter
             * @param val
             * The val parameter refers to new value
             */
            void setOpacity(std::uint8_t val)
            { this->_a = val; }

            /*!
             * red value getter
             * @return
             * This method return the red value of the color
             */
            [[nodiscard]] std::uint8_t getRed() const
            { return this->_r; }

            /*!
             * green value getter
             * @return
             * This method return the green value of the color
             */
            [[nodiscard]] std::uint8_t getGreen() const
            { return this->_g; }

            /*!
             * blue value getter
             * @return
             * This method return the blue value of the color
             */
            [[nodiscard]] std::uint8_t getBlue() const
            { return this->_b; }

            /*!
             * opacity value getter
             * @return
             * This method return the opacity value of the color
             */
            [[nodiscard]] std::uint8_t getOpacity() const
            { return this->_a; }

        private:
            std::uint8_t _r;
            std::uint8_t _g;
            std::uint8_t _b;
            std::uint8_t _a;
    };
}

#endif //COLOR_HPP
