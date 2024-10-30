#include <iostream>
#include <display/Curses.hpp>

extern "C"
[[nodiscard]][[maybe_unused]] interfaces::IGraphical *entryPoint()
{
    std::cout << "Initializing Curses..." << std::endl;
    return new display::Curses();
}

extern "C"
[[nodiscard]][[maybe_unused]] arcade::InterfaceType getType()
{
    return (arcade::InterfaceType::IGraphical);
}