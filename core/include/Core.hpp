#ifndef CORE_HPP
#define CORE_HPP

#include <any>
#include <string>
#include <unordered_map>
#include <vector>
#include <interfaces/IGraphical.hpp>
#include <interfaces/IGame.hpp>
#include <misc/DLWrapper.hpp>

/*!
 * @namespace Core
 * @brief The namespace Core contains various classes that will be used to make the Core work
 */
namespace core
{
    /*!
     * @class Core::Core
     * @brief The Core class contains methods that will manage dynamic loading of libraries, call of libraries functions, etc..
     */
    class Core
    {
        public:
            explicit Core(const std::string &base_lib);
            ~Core();

            /*!
             * @brief The updateAvailableLibs method is a method that will update both game and graphical available libraries.
             */
            void updateAvailableLibs();

            /*!
             * @brief The updateAvailableGraphicalLibs method is a method that will update available graphical libraries.
             */
            void updateAvailableGraphicalLibs();

            /*!
             * @brief The updateAvailableGameLibs method is a method that will update available game libraries.
             */
            void updateAvailableGameLibs();

            /*!
             * @brief The setGraphicalLib method is a method that will switch the graphical library to the one with the given number (index of a lib in the availableGraphicalLibs).
             * @param lib_number
             */
            void setGraphicalLib(std::uint64_t lib_number);

            /*!
             * @brief The setGraphicalLib method is a method that will switch the game library to the one with the given number (index of a lib in the availableGameLibs).
             * @param lib_number
             */
            void setGameLib(std::uint64_t lib_number);

            /*!
             * @brief The loop method is the arcade project main loop.
             */
            void loop();

            /*!
             * @brief Getter for available game libs.
             */
            [[nodiscard]] const std::vector<std::string> &getAvailableGameLibs() const
            { return this->_availableGamesLibs; }

            /*!
             * @brief Getter for available graphics libs.
             */
            [[nodiscard]] const std::vector<std::string> &getAvailableGraphicsLibs() const
            { return this->_availableGraphicalLibs; }

        private:
            static void _emptyQueues(arcade::protocols::DisplayProtocol &renderQueues);
            void _greeterDone();
            void _rotateGraphicalLibrary();
            void _rotateGameLibrary();
            void _startGraphicalLibrary(const std::string &path);
            void _startGameLibrary(const std::string &path);
            void _transmitCommands(
                std::queue<arcade::resources::Keys> &windowEvents,
                std::queue<arcade::resources::Keys> &gameEvents
            );
            bool _interceptCommand(arcade::resources::Keys);
            template <typename T>
            void _loadLibrary(const std::string &path)
            {
                auto lib = std::make_unique<misc::DLWrapper>(path);
                std::any res;

                if (std::is_same<T, interfaces::IGame>::value)
                    res = lib->getSymbol<T *(std::string &)>("entryPoint");
                else
                    res = lib->getSymbol<T *()>("entryPoint");
                this->_loaded.insert(
                    std::pair<std::string, std::pair<std::unique_ptr<misc::DLWrapper>, std::any>>({
                        path,
                        std::pair<std::unique_ptr<misc::DLWrapper>, std::any>({
                            std::move(lib),
                            res
                        })
                    })
                );
            }

            bool _loop;
            bool _greeter;
            std::string _username;
            std::uint64_t _gameLibIndex;
            std::uint64_t _graphicalLibIndex;
            std::vector<std::string> _availableGamesLibs;
            std::vector<std::string> _availableGraphicalLibs;
            std::unique_ptr<interfaces::IGraphical> _currentGraphicalLib;
            std::unique_ptr<interfaces::IGame> _currentGameLib;
            std::unordered_map<std::string, std::pair<std::unique_ptr<misc::DLWrapper>, std::any>> _loaded;
            static const std::array<std::string, 5> _gameLibs;
            static const std::array<std::string, 13> _graphicalLibs;
    };
}

#endif //CORE_HPP
