#include <thread>
#include <display/Sdl.hpp>
#include <unistd.h>

display::Sdl::Sdl() :
_wrapper(),
_lastTime(std::chrono::high_resolution_clock::now()),
_clock(std::chrono::high_resolution_clock::now())
{
}

display::Sdl::~Sdl()
{
    this->_wrapper.clear();
}

void display::Sdl::_displaySprite(std::queue<arcade::resources::Sprite> &sprites)
{
    while (!sprites.empty()) {
        const auto spriteToDisplay = sprites.front();
        this->_wrapper.setSurface(spriteToDisplay.spritePath.c_str());
        this->_wrapper.setTexture();
        this->_wrapper.setSrcRect(
            static_cast<int>(spriteToDisplay.spriteArea.x),
            static_cast<int>(spriteToDisplay.spriteArea.y),
            static_cast<int>(spriteToDisplay.spriteArea.w),
            static_cast<int>(spriteToDisplay.spriteArea.h)
        );
        this->_wrapper.setDstRect(
            static_cast<int>(spriteToDisplay.coords.x),
            static_cast<int>(spriteToDisplay.coords.y),
            static_cast<int>(spriteToDisplay.spriteArea.w),
            static_cast<int>(spriteToDisplay.spriteArea.h)
        );
        this->_wrapper.spriteRender();
        sprites.pop();
    }
}

void display::Sdl::_displayText(std::queue<arcade::resources::Text> &texts)
{
    while (!texts.empty()) {
        const auto textToDisplay = texts.front();
        this->_wrapper.setFont(textToDisplay.fontPath.c_str(), textToDisplay.fontSize);
        this->_wrapper.setColor(
            textToDisplay.color.getRed(),
            textToDisplay.color.getGreen(),
            textToDisplay.color.getBlue(),
            textToDisplay.color.getOpacity()
        );
        this->_wrapper.setTextSurface(textToDisplay.text.c_str());
        this->_wrapper.setTextTexture();
        this->_wrapper.setDstRect(static_cast<int>(textToDisplay.coords.x),
            static_cast<int>(textToDisplay.coords.y),
            this->_wrapper.getTextSurface()->w, this->_wrapper.getTextSurface()->h);
        this->_wrapper.textRender();
        texts.pop();
    }
}

void display::Sdl::render(arcade::protocols::DisplayProtocol &toRender)
{
    this->_delayFps();
    this->_wrapper.clear();
    this->_displaySprite(toRender.sprites);
    this->_displayText(toRender.texts);
    this->_wrapper.display();
}

void display::Sdl::collectEvents(std::queue<arcade::resources::Keys> &events)
{
    this->_wrapper.getEvents(events);
}

void display::Sdl::updateTime(arcade::Time &dt)
{
    std::chrono::time_point<std::chrono::high_resolution_clock> now_time = std::chrono::high_resolution_clock::now();

    dt = (std::chrono::duration<double, std::milli>(now_time - this->_lastTime).count()) * 0.001;
    this->_lastTime = std::chrono::high_resolution_clock::now();
}

void display::Sdl::_delayFps()
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