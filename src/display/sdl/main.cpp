#include <iostream>
#include <display/Sdl.hpp>

extern "C"
[[nodiscard]][[maybe_unused]] interfaces::IGraphical *entryPoint()
{
    std::cout << "Initializing SDL..." << std::endl;
    return new display::Sdl();
}

extern "C"
[[nodiscard]][[maybe_unused]] arcade::InterfaceType getType()
{
    return (arcade::InterfaceType::IGraphical);
}
