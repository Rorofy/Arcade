#include <iostream>
#include <interfaces/IGame.hpp>
#include "include/Nibbler.hpp"

/*!
 * entryPoint is a function that will be called to load the Game library.
 */
extern "C"
[[nodiscard]][[maybe_unused]] interfaces::IGame *entryPoint(const std::string &username)
{
    std::cout << "Initializing Nibbler..." << std::endl;
    return new games::Nibbler(username);
}

/*!
 * getType is a function that returns the type of library.
 */
extern "C"
[[nodiscard]][[maybe_unused]] arcade::InterfaceType getType()
{
    return (arcade::InterfaceType::IGame);
}
