#include <display/Sfml.hpp>

display::Sfml::Sfml()
    : _window(sf::VideoMode(arcade::WIN_WIDTH, arcade::WIN_HEIGHT), "Arcade"), _clock()
{
    this->_window.setFramerateLimit(arcade::FRAMERATE);
}

display::Sfml::~Sfml()
{
    this->_window.clear(sf::Color::Black);
    this->_window.close();
}

void display::Sfml::_displaySprite(std::queue<arcade::resources::Sprite> &sprites)
{
    sf::Texture texture;
    sf::Sprite sprite;

    while (!sprites.empty()) {
        const auto spriteToDisplay = sprites.front();
        texture.loadFromFile(spriteToDisplay.spritePath,
            sf::IntRect(
                spriteToDisplay.spriteArea.x,
                spriteToDisplay.spriteArea.y,
                spriteToDisplay.spriteArea.w,
                spriteToDisplay.spriteArea.h
            )
        );
        sprite.setTexture(texture);
        sprite.setPosition(spriteToDisplay.coords.x, spriteToDisplay.coords.y);
        this->_window.draw(sprite);
        sprites.pop();
    }
}

void display::Sfml::_displayText(std::queue<arcade::resources::Text> &texts)
{
    sf::Font font;
    sf::Text text;

    while (!texts.empty()) {
        const auto textToDisplay = texts.front();
        font.loadFromFile(textToDisplay.fontPath);
        text.setFont(font);
        text.setString(textToDisplay.text);
        text.setCharacterSize(textToDisplay.fontSize);
        text.setFillColor(sf::Color(
            textToDisplay.color.getRed(),
            textToDisplay.color.getGreen(),
            textToDisplay.color.getBlue(),
            textToDisplay.color.getOpacity()
        ));
        text.setPosition(textToDisplay.coords.x, textToDisplay.coords.y);
        this->_window.draw(text);
        texts.pop();
    }
}

void display::Sfml::render(arcade::protocols::DisplayProtocol &toRender)
{
    this->_window.clear(sf::Color::Black);
    this->_displaySprite(toRender.sprites);
    this->_displayText(toRender.texts);
    this->_window.display();
}

void display::Sfml::collectEvents(std::queue<arcade::resources::Keys> &events)
{
    sf::Event event;

    while (this->_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            events.push(arcade::resources::Keys::Close);
            break;
        }
        if (event.type == sf::Event::KeyPressed) {
            const auto evt = arcade::resources::FROM_SFML.find(event.key.code);
            if (evt != arcade::resources::FROM_SFML.end())
                events.push(evt->second);
        }
    }
}

void display::Sfml::updateTime(arcade::Time &dt)
{
    dt = this->_clock.getElapsedTime().asSeconds();
    this->_clock.restart();
}
