#include <iostream>
#include <interfaces/IGame.hpp>
#include "include/SolarFox.hpp"

/*!
 * entryPoint is a function that will be called to load the Game library.
 */
extern "C"
[[nodiscard]][[maybe_unused]] interfaces::IGame *entryPoint(const std::string &username)
{
    std::cout << "Initializing SolarFox..." << std::endl;
    return new games::SolarFox(username);
}

/*!
 * getType is a function that returns the type of library.
 */
extern "C"
[[nodiscard]][[maybe_unused]] arcade::InterfaceType getType()
{
    return (arcade::InterfaceType::IGame);
}