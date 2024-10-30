#ifndef DLWRAPPER_HPP
#define DLWRAPPER_HPP

#include <memory>
#include <link.h>
#include <queue>
#include <functional>
#include <exceptions/FileNotCompatible.hpp>

/*!
 * @namespace Misc
 * @brief The Misc namespace contains data that doesnt belong to any particular category
 */
namespace misc
{
    /*!
     * @class DLWrapper
     * @brief the DLWrapper class is an encapsulation of the libdl
     */
    class DLWrapper
    {
        public:
            /*!
             * constructor
             * @param path
             * the path parameter refers to the path to get the lib from binary
             */
            explicit DLWrapper(const std::basic_string_view<char> &path);
            ~DLWrapper();

            /*!
             * the getSymbol function is a function that allows you to get a symbol from the shared library
             * @tparam T
             * the T template refers to prototype of the function you wanna load
             * @param symName
             * symName refers to the symbol name
             * @return
             * returns a std::function that contains the pointer to the symbol
             */
            template <typename T>
            std::function<T> getSymbol(const std::string &symName)
            {
                T *ptr = reinterpret_cast<T *>(dlsym(this->_handle, symName.data()));

                if (ptr == NULL)
                    throw arcade::exceptions::FileNotCompatible(dlerror());
                return (std::function<T>(ptr));
            }

        private:
            void *_handle;
    };
}

#endif //DLWRAPPER_HPP
