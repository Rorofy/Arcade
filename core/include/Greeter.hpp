#ifndef GREETER_HPP
#define GREETER_HPP

#include <interfaces/IGame.hpp>

/*!
 * @namespace Core
 * @brief The namespace Core contains various classes that will be used to make the Core work
 */
namespace core
{
    /*!
     * @class Greeter
     * @brief The class Greeter serves the purpose of representing the startup menu and all of its functionalities. It's a class that must be used on startup.
     */
    class Greeter : public interfaces::IGame
    {
        public:
            Greeter(const std::vector<std::string> &availableGamesLibs);

            void tick(std::queue<arcade::resources::Keys> &events, arcade::Time &dt) override;
            void prepareRendering(arcade::protocols::DisplayProtocol &renderQueues) const override;

            /*!
             * The greeter method getUsername returns the username variable
             * @return The username variable
             */
            [[nodiscard]] const std::string &getUsername() const
            { return this->_username; }

            /*!
             * The greeter method getUsername returns the username variable
             * @return The username variable
             */
            [[nodiscard]] std::uint32_t getSelectedGameLibrary() const
            { return this->_selectedGameLibrary; }

            /*!
             * The greeter method done returns if the user chosen everything
             * @return True if the greeter is not useful anymore
             */
            [[nodiscard]] bool done() const
            { return (this->_state == EditState::DONE); };

            ~Greeter() = default;
        private:
            enum EditState
            {
                USERNAME,
                GAME,
                DONE
            };

            static const uint32_t USERNAME_PROMPT_W = 200;
            static const uint32_t USERNAME_PROMPT_H = 75;
            static const uint32_t MAX_USERNAME_LENGTH = 10;

            void _addKeyToUsername(const arcade::resources::Keys &cur);
            void _choseGameLibrary(const arcade::resources::Keys &cur);

            void _drawUsernamePrompt(arcade::protocols::DisplayProtocol &renderQueues) const;
            void _drawGameSelection(arcade::protocols::DisplayProtocol &renderQueues) const;
            static void _drawBackground(arcade::protocols::DisplayProtocol &renderQueues);

            std::string _username;
            std::uint32_t _selectedGameLibrary;
            EditState _state;

            const std::vector<std::string> &_availableGamesLibs;
    };
}

#endif //GREETER_HPP
