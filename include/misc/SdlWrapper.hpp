#ifndef SDLWRAPPER_HPP
#define SDLWRAPPER_HPP

#include <iostream>
#include <memory>
#include <queue>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <Common.hpp>
#include <resources/Keys.hpp>
#include <resources/KeyTranslation.hpp>


/*!
 * @namespace Misc
 * @brief The Misc namespace contains data that doesnt belong to any particular category
 */
namespace misc
{
    /*!
     * @class SdlWrapper
     * @brief the SdlWrapper class is an encapsulation of the lib ncurses
     */
    class SdlWrapper
    {
        public:
            SdlWrapper();
            ~SdlWrapper();

            /*!
            * @brief the setSurface method is a method that sets the private _surface
            * @param path
            * path is the filepath of the sprite
            */
            void setSurface(const char *path);

            /*!
            * @brief the setTextSurface method is a method that sets the private _textSurface
            * @param str
            * str is string of the text
            */
            void setTextSurface(const char *str);

            /*!
            * @brief the setTexture method is a method that sets the private _texture
            */
            void setTexture();

            /*!
            * @brief the setTextTexture method is a method that sets the private _textTexture
            */
            void setTextTexture();

            /*!
            * @brief the setFont method is a method that sets the private _font
            * @param path
            * path is the filepath to the font
            * @param size
            * size is the size of the characters that will be displayed
            */
            void setFont(const char *path, std::uint32_t size);

            /*!
            * @brief the setSrcRect method is a method that sets the private _srcRect
            * @param x
            * x is the abscissa of the top left of the rectangle
            * @param y
            * y is the ordinate of the top left of the rectangle
            * @param w
            * w is the width of the rectangle
            * @param h
            * h is the height of the rectangle
            */
            void setSrcRect(int x, int y, int w, int h);

            /*!
            * @brief the setSrcRect method is a method that sets the private _dstRect
            * @param x
            * x is the abscissa of the top left of the rectangle
            * @param y
            * y is the ordinate of the top left of the rectangle
            * @param w
            * w is the width of the rectangle
            * @param h
            * h is the height of the rectangle
            */
            void setDstRect(int x, int y, int w, int h);

            /*!
            * @brief the setColor method is a method that sets the private _color
            * @param r
            * r is the red component of the color
            * @param g
            * g is the green component of the color
            * @param b
            * b is the blue component of the color
            * @param o
            * o is the alpha component, the opacity of the color
            */
            void setColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t o);

            /*!
            * @brief the queryTexture method is a method that call the queryTexture function from SDL
            * @param texW
            * texW is the width of the texture
            * @param texH
            * texH is the height of the texture
            */
            void queryTexture(int *texW, int *texH);

            /*!
            * @brief the spriteRender method is a method that render the sprites
            */
            void spriteRender();

            /*!
            * @brief the textRender method is a method that render the texts
            */
            void textRender();

            /*!
            * @brief the clear method is a method that clear everything that is displayed
            */
            void clear();

            /*!
            * @brief the display method is a method that display everything rendered
            */
            void display();

            /*!
            * @brief the getEvents method is a method that get the events from the game
            * @param events
            * events is a queue of events that are received
            */
            void getEvents(std::queue<arcade::resources::Keys> &events);

            /*!
            * @brief the getTextSurface method is a method that returns the private variable _textSurface
            */
            SDL_Surface *getTextSurface();

        private:
            std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>_window;
	        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer;
            std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> _surface;
            std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> _textSurface;
            std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _texture;
            std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _textTexture;
            std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> _font;
            SDL_Rect _srcRect;
            SDL_Rect _dstRect;
            SDL_Color _color;
    };
}

#endif //SDLWRAPPER_HPP
