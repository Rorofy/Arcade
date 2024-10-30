#include <iostream>
#include <Common.hpp>
#include <ctime>
#include "core/include/Core.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Invalid number of arguments" << std::endl;
        return (arcade::EXIT_ERR);
    } else {
        std::srand(std::time(nullptr));
        try {
            core::Core core(av[1]);

            core.loop();
        } catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
            return (arcade::EXIT_ERR);
        } catch (...) {
            std::cerr << "ESPECE DE GROSSE MERDE, fait une exception qui hérite de std::exception";
            return (arcade::EXIT_ERR);
        }
    }
    return (0);
}