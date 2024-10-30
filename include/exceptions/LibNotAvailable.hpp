#include <utility>
#include <cstdint>
#include <string>

#ifndef LIBNOTAVAILABLE_HPP
#define LIBNOTAVAILABLE_HPP

/*!
 * @namespace Exceptions
 * @brief The Exceptions namespace contains various exceptions that are needed to make the arcade work
 */
namespace arcade::exceptions
{
    /*!
     * @class FileNotCompatible
     * @brief The LibNotAvailable class is an exception that will be thrown if the user try to switch to a library that is not available
     */
    class LibNotAvailable : public std::exception
    {
        public:
            explicit LibNotAvailable(std::uint64_t libIndex, const std::vector<std::string> &availableLibs)
            {
                std::uint64_t i = 0;
                this->_msg =
                    "Trying to load an unavailable library (" +
                    std::to_string(libIndex) +
                    "), available libs:\n";

                if (!availableLibs.empty()) {
                    for (; i < availableLibs.size() - 1; i++)
                        this->_msg += "\t- " + availableLibs[i] + " (" + std::to_string(i) + ")\n";
                    this->_msg += "\t- " + availableLibs[i] + " (" + std::to_string(i) + ")";
                }
            }

            [[nodiscard]] const char *what() const noexcept override
            {
                return (this->_msg.c_str());
            };

        private:
            std::string _msg;
    };
}

#endif //LIBNOTAVAILABLE_HPP
