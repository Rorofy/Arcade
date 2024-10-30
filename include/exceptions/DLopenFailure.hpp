#ifndef DLOPENFAILURE_HPP
#define DLOPENFAILURE_HPP

#include <exception>

/*!
 * @namespace Exceptions
 * @brief The Exceptions namespace contains various exceptions that are needed to make the arcade work
 */
namespace arcade::exceptions
{
    /*!
     * @class DLopenFailure
     * @brief The FileNotCompatible class is an exception that will be thrown if dlopen fails
     */
    class DLopenFailure : public std::exception
    {
        public:
            explicit DLopenFailure(const std::string &dlerror, const std::string &path, const std::string &mode)
            {
                this->_msg =
                    "Dlopen call failed."
                    "\n\t- Path: " +
                    path +
                    "\n\t- Mode: " +
                    mode +
                    "\nReason:\n" +
                    dlerror;
            }

            [[nodiscard]] const char *what() const noexcept override
            {
                return (this->_msg.c_str());
            };

        private:
            std::string _msg;
    };
}

#endif //DLOPENFAILURE_HPP
