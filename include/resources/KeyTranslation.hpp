#ifndef KEYTRANSLATION_HPP
#define KEYTRANSLATION_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <curses.h>
#include <resources/Keys.hpp>

/*!
 * @namespace Resources
 * @brief The Resources namespace contains all arcade resources
 */
namespace arcade::resources {

    /*!
     *  @brief This unordered_map translates all the nCurses bindings into Arcade compatible format
     */
    static const std::unordered_map<int, arcade::resources::Keys> FROM_CURSES = {
        {-1,  arcade::resources::Keys::Unknown},
        {'a', arcade::resources::Keys::A},
        {'b', arcade::resources::Keys::B},
        {'c', arcade::resources::Keys::C},
        {'d', arcade::resources::Keys::D},
        {'e', arcade::resources::Keys::E},
        {'f', arcade::resources::Keys::F},
        {'g', arcade::resources::Keys::G},
        {'h', arcade::resources::Keys::H},
        {'i', arcade::resources::Keys::I},
        {'j', arcade::resources::Keys::J},
        {'k', arcade::resources::Keys::K},
        {'l', arcade::resources::Keys::L},
        {'m', arcade::resources::Keys::M},
        {'n', arcade::resources::Keys::N},
        {'o', arcade::resources::Keys::O},
        {'p', arcade::resources::Keys::P},
        {'q', arcade::resources::Keys::Q},
        {'r', arcade::resources::Keys::R},
        {'s', arcade::resources::Keys::S},
        {'t', arcade::resources::Keys::T},
        {'u', arcade::resources::Keys::U},
        {'v', arcade::resources::Keys::V},
        {'w', arcade::resources::Keys::W},
        {'x', arcade::resources::Keys::X},
        {'y', arcade::resources::Keys::Y},
        {'z', arcade::resources::Keys::Z},
        {27, arcade::resources::Keys::Escape},
        {' ', arcade::resources::Keys::Space},
        {10, arcade::resources::Keys::Enter},
        {KEY_LEFT, arcade::resources::Keys::Left},
        {KEY_RIGHT, arcade::resources::Keys::Right},
        {KEY_UP, arcade::resources::Keys::Up},
        {KEY_DOWN, arcade::resources::Keys::Down},
        {KEY_BACKSPACE, arcade::resources::Keys::Return}
    };

    /*!
     *  @brief This unordered_map translates all the SFML bindings into Arcade compatible format
     */
    static const std::unordered_map<sf::Keyboard::Key, arcade::resources::Keys> FROM_SFML = {
        {sf::Keyboard::Key::Unknown, arcade::resources::Keys::Unknown},
        {sf::Keyboard::Key::A, arcade::resources::Keys::A},
        {sf::Keyboard::Key::B, arcade::resources::Keys::B},
        {sf::Keyboard::Key::C, arcade::resources::Keys::C},
        {sf::Keyboard::Key::D, arcade::resources::Keys::D},
        {sf::Keyboard::Key::E, arcade::resources::Keys::E},
        {sf::Keyboard::Key::F, arcade::resources::Keys::F},
        {sf::Keyboard::Key::G, arcade::resources::Keys::G},
        {sf::Keyboard::Key::H, arcade::resources::Keys::H},
        {sf::Keyboard::Key::I, arcade::resources::Keys::I},
        {sf::Keyboard::Key::J, arcade::resources::Keys::J},
        {sf::Keyboard::Key::K, arcade::resources::Keys::K},
        {sf::Keyboard::Key::L, arcade::resources::Keys::L},
        {sf::Keyboard::Key::M, arcade::resources::Keys::M},
        {sf::Keyboard::Key::N, arcade::resources::Keys::N},
        {sf::Keyboard::Key::O, arcade::resources::Keys::O},
        {sf::Keyboard::Key::P, arcade::resources::Keys::P},
        {sf::Keyboard::Key::Q, arcade::resources::Keys::Q},
        {sf::Keyboard::Key::R, arcade::resources::Keys::R},
        {sf::Keyboard::Key::S, arcade::resources::Keys::S},
        {sf::Keyboard::Key::T, arcade::resources::Keys::T},
        {sf::Keyboard::Key::U, arcade::resources::Keys::U},
        {sf::Keyboard::Key::V, arcade::resources::Keys::V},
        {sf::Keyboard::Key::W, arcade::resources::Keys::W},
        {sf::Keyboard::Key::X, arcade::resources::Keys::X},
        {sf::Keyboard::Key::Y, arcade::resources::Keys::Y},
        {sf::Keyboard::Key::Z, arcade::resources::Keys::Z},
        {sf::Keyboard::Key::Escape, arcade::resources::Keys::Escape},
        {sf::Keyboard::Key::Space, arcade::resources::Keys::Space},
        {sf::Keyboard::Key::Enter, arcade::resources::Keys::Enter},
        {sf::Keyboard::Key::Left, arcade::resources::Keys::Left},
        {sf::Keyboard::Key::Right, arcade::resources::Keys::Right},
        {sf::Keyboard::Key::Up, arcade::resources::Keys::Up},
        {sf::Keyboard::Key::Down, arcade::resources::Keys::Down},
        {sf::Keyboard::Key::Backspace, arcade::resources::Keys::Return}
    };

    /*!
     * @brief This unordered_map translates all the SDL2 bindings into Arcade compatible format
     */
    static const std::unordered_map<SDL_Keycode, arcade::resources::Keys> FROM_SDL = {
        {SDLK_UNKNOWN, arcade::resources::Keys::Unknown},
        {SDLK_a, arcade::resources::Keys::A},
        {SDLK_b, arcade::resources::Keys::B},
        {SDLK_c, arcade::resources::Keys::C},
        {SDLK_d, arcade::resources::Keys::D},
        {SDLK_e, arcade::resources::Keys::E},
        {SDLK_f, arcade::resources::Keys::F},
        {SDLK_g, arcade::resources::Keys::G},
        {SDLK_h, arcade::resources::Keys::H},
        {SDLK_i, arcade::resources::Keys::I},
        {SDLK_j, arcade::resources::Keys::J},
        {SDLK_k, arcade::resources::Keys::K},
        {SDLK_l, arcade::resources::Keys::L},
        {SDLK_m, arcade::resources::Keys::M},
        {SDLK_n, arcade::resources::Keys::N},
        {SDLK_o, arcade::resources::Keys::O},
        {SDLK_p, arcade::resources::Keys::P},
        {SDLK_q, arcade::resources::Keys::Q},
        {SDLK_r, arcade::resources::Keys::R},
        {SDLK_s, arcade::resources::Keys::S},
        {SDLK_t, arcade::resources::Keys::T},
        {SDLK_u, arcade::resources::Keys::U},
        {SDLK_v, arcade::resources::Keys::V},
        {SDLK_w, arcade::resources::Keys::W},
        {SDLK_x, arcade::resources::Keys::X},
        {SDLK_y, arcade::resources::Keys::Y},
        {SDLK_z, arcade::resources::Keys::Z},
        {SDLK_ESCAPE, arcade::resources::Keys::Escape},
        {SDLK_SPACE, arcade::resources::Keys::Space},
        {SDLK_RETURN, arcade::resources::Keys::Enter},
        {SDLK_LEFT, arcade::resources::Keys::Left},
        {SDLK_RIGHT, arcade::resources::Keys::Right},
        {SDLK_UP, arcade::resources::Keys::Up},
        {SDLK_DOWN, arcade::resources::Keys::Down},
        {SDLK_BACKSPACE, arcade::resources::Keys::Return}
    };
}

#endif //KEYTRANSLATION_HPP
