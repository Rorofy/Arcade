#include "resources/Color.hpp"

arcade::resources::Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t opacity)
    : _r(red), _g(green), _b(blue), _a(opacity)
{}
