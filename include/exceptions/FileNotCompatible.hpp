#ifndef FILENOTCOMPATIBLE_HPP
#define FILENOTCOMPATIBLE_HPP

#include <string_view>
#include <exception>

/*!
 * @namespace Exceptions
 * @brief The Exceptions namespace contains various exceptions that are needed to make the arcade work
 */
namespace arcade::exceptions
{
    /*!
     * @class FileNotCompatible
     * @brief The FileNotCompatible class is an exception that will be thrown if the user give an non-implemented file
     */
    class FileNotCompatible : public std::exception
    {
        public:
            explicit FileNotCompatible(const char *msg)
                : _msg(msg)
            {}

            [[nodiscard]] const char *what() const noexcept override
            {
                return (this->_msg);
            };

        private:
            const char *_msg;
    };
}
#endif //FILENOTCOMPATIBLE_HPP
