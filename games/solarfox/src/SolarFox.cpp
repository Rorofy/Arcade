#include "../include/SolarFox.hpp"

void games::SolarFox::tick(__attribute__((unused))std::queue<arcade::resources::Keys> &events, __attribute__((unused))arcade::Time &dt)
{
}

void games::SolarFox::prepareRendering(__attribute__((unused))arcade::protocols::DisplayProtocol &renderQueues) const
{
}

games::SolarFox::SolarFox(const std::string &username)
    : _username(username)
{
}
