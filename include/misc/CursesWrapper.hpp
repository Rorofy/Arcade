#ifndef CURSESWRAPPER_HPP
#define CURSESWRAPPER_HPP

#include <iostream>
#include <curses.h>
#include <Common.hpp>

/*!
 * @namespace Misc
 * @brief The Misc namespace contains data that doesnt belong to any particular category
 */
namespace misc
{
    /*!
     * @class CursesWrapper
     * @brief the CursesWrapper class is an encapsulation of the lib ncurses
     */
    class CursesWrapper
    {
        public:
            CursesWrapper();
            ~CursesWrapper();

            /*!
            * @brief The displayChar method is a method display a character representing a sprite
            * @param color
            * color is the color of the character that will be displayed
            * @param termCoords
            * termCoords are the x and y coordinates where the character will be displayed
            * @param termChar
            * termChar is the character that will be displayed
            */
            void displayChar(std::uint16_t color, arcade::Coords<int> termCoords, std::uint32_t termChar);

            /*!
            * @brief The displayStr method is a method display a string representing a text
            * @param color
            * color is the color of the text that will be displayed
            * @param termCoords
            * termCoords are the x and y coordinates where the text will be displayed
            * @param text
            * termChar is the text that will be displayed
            */
            void displayStr(std::uint16_t color, arcade::Coords<int> termCoords, const std::string& text);

            /*!
            * @brief The wrapperClear method is a method that will wrapperClear everything displayed
            */
            void wrapperClear();

            /*!
            * @brief The wrapperRefresh method is a method that will wrapperRefresh, render and display the game
            */
            void wrapperRefresh();

            /*!
            * @brief The getEvent method is a method that will get events from keyboards while in game
            */
            int16_t getEvent();

            /*!
            * @brief The initColor method is a method that will initialise the color to be displayed afterwards
            * @param COLOR
            * @param red
            * @param green
            * @param blue
            */
            void initColor(short COLOR, short red, short green, short blue);

            /*!
            * @brief The initPair method is a method that will initialise the pair of color to be displayed afterwards
            * @param pair
            * @param color1
            * @param color2
            */
            void initPair(short pair, short color1, short color2);
    };
}

#endif //CURSESWRAPPER_HPP
