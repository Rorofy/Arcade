#include <iostream>
#include <display/Sfml.hpp>

extern "C"
[[nodiscard]][[maybe_unused]] interfaces::IGraphical *entryPoint()
{
    std::cout << "Initializing SFML..." << std::endl;
    return new display::Sfml();
}

extern "C"
[[nodiscard]][[maybe_unused]] arcade::InterfaceType getType()
{
    return (arcade::InterfaceType::IGraphical);
}