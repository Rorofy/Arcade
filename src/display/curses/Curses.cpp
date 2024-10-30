#include <thread>
#include <iostream>
#include <display/Curses.hpp>
#include <misc/CursesWrapper.hpp>
#include <unistd.h>

display::Curses::Curses() :
_lastTime(std::chrono::high_resolution_clock::now()),
_clock(std::chrono::high_resolution_clock::now()),
_wrapper()
{
}

display::Curses::~Curses()
{
    this->_wrapper.wrapperClear();
}

void display::Curses::_displaySprite(std::queue<arcade::resources::Sprite> &sprites)
{
    while (!sprites.empty()) {
        const auto spriteToDisplay = sprites.front();
        if (spriteToDisplay.termDisplay == arcade::resources::Sprite::PIXEL) {
            std::uint16_t color = this->_getPosixColor(arcade::resources::BACKGROUND, spriteToDisplay.termColor);
            this->_wrapper.displayChar(color, spriteToDisplay.termCoords, spriteToDisplay.termChar);
        } else {
            std::uint16_t color = this->_getPosixColor(arcade::resources::FOREGROUND, spriteToDisplay.termColor);
            this->_wrapper.displayChar(color, spriteToDisplay.termCoords, spriteToDisplay.termChar);
        }
        sprites.pop();
    }
}

void display::Curses::_displayText(std::queue<arcade::resources::Text> &texts)
{
    while (!texts.empty()) {
        const auto textToDisplay = texts.front();
        std::uint16_t color = this->_getPosixColor(arcade::resources::FOREGROUND, textToDisplay.color);
        this->_wrapper.displayStr(color, textToDisplay.termCoords, textToDisplay.text);
        texts.pop();
    }
}

void display::Curses::render(arcade::protocols::DisplayProtocol &toRender)
{
    this->_delayFps();
    this->_wrapper.wrapperClear();
    this->_displaySprite(toRender.sprites);
    this->_displayText(toRender.texts);
    this->_wrapper.wrapperRefresh();
}

void display::Curses::collectEvents(std::queue<arcade::resources::Keys> &events)
{
    std::int16_t ch = 0;

    while (ch != ERR) {
        ch = this->_wrapper.getEvent();
        const auto evt = arcade::resources::FROM_CURSES.find(ch);
        if (evt != arcade::resources::FROM_CURSES.end())
            events.push(evt->second);
    }
}

void display::Curses::updateTime(arcade::Time &dt)
{
    const auto now_time = std::chrono::high_resolution_clock::now();

    dt = (std::chrono::duration<double, std::milli>(now_time - this->_lastTime).count()) * 0.001;
    this->_lastTime = std::chrono::high_resolution_clock::now();
}

void display::Curses::_delayFps()
{
    static uint8_t start = 0;
    const auto now = std::chrono::high_resolution_clock::now();
    
    if (start == 0)
        start = 1;
    else {
        std::chrono::milliseconds toSleep(17 - std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_clock).count());
        std::this_thread::sleep_for(toSleep);
    }
    this->_clock = std::chrono::high_resolution_clock::now();
}

[[nodiscard]] std::uint16_t display::Curses::_getPosixColor(arcade::resources::ColorType type,
                                                            arcade::resources::Color color)
{
    static uint16_t IDX_PAIR = 0;
    static uint16_t COLOR = 0;

    IDX_PAIR++;
    COLOR++;
    this->_wrapper.initColor(
        COLOR,
        static_cast<short>(color.getRed() / 255 * 1000),
        static_cast<short>(color.getGreen() / 255 * 1000),
        static_cast<short>(color.getBlue() / 255 * 1000)
    );
    if (type == arcade::resources::ColorType::FOREGROUND)
        this->_wrapper.initPair(IDX_PAIR, COLOR, COLOR_BLACK);
    else
        this->_wrapper.initPair(IDX_PAIR, COLOR, COLOR);
    return IDX_PAIR;
}