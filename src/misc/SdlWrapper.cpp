#include <misc/SdlWrapper.hpp>

misc::SdlWrapper::SdlWrapper() :
_window(nullptr, SDL_DestroyWindow),
_renderer(nullptr, SDL_DestroyRenderer),
_surface(nullptr, SDL_FreeSurface),
_textSurface(nullptr, SDL_FreeSurface),
_texture(nullptr, SDL_DestroyTexture),
_textTexture(nullptr, SDL_DestroyTexture),
_font(nullptr, TTF_CloseFont),
_srcRect(),
_dstRect(),
_color()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    this->_window.reset(SDL_CreateWindow("Arcade", 0, 0, arcade::WIN_WIDTH, arcade::WIN_HEIGHT, 0));
    this->_renderer.reset(SDL_CreateRenderer(this->_window.get(), -1, SDL_RENDERER_ACCELERATED));
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
}

misc::SdlWrapper::~SdlWrapper()
{
    this->_window.reset();
    this->_renderer.reset();
    this->_surface.reset();
    this->_textSurface.reset();
    this->_texture.reset();
    this->_textTexture.reset();
    this->_font.reset();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void misc::SdlWrapper::setSurface(const char *path)
{
    this->_surface.reset(IMG_Load(path));
}

void misc::SdlWrapper::setTextSurface(const char *path)
{
    this->_textSurface.reset(TTF_RenderText_Solid(this->_font.get(), path, this->_color));
}

void misc::SdlWrapper::setTexture()
{
    this->_texture.reset(SDL_CreateTextureFromSurface(this->_renderer.get(), this->_surface.get()));
}

void misc::SdlWrapper::setTextTexture()
{
    this->_textTexture.reset(SDL_CreateTextureFromSurface(this->_renderer.get(), this->_textSurface.get()));
}

void misc::SdlWrapper::setFont(const char *path, std::uint32_t size)
{
    this->_font.reset(TTF_OpenFont(path, size));
}

void misc::SdlWrapper::setSrcRect(int x, int y, int w, int h)
{
    this->_srcRect = {x, y, w, h};
}

void misc::SdlWrapper::setDstRect(int x, int y, int w, int h)
{
    this->_dstRect = {x, y, w, h};
}

void misc::SdlWrapper::setColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t o)
{
    this->_color = {r, g, b, o};
}

void misc::SdlWrapper::queryTexture(int *texW, int *texH)
{
    SDL_QueryTexture(this->_textTexture.get(), nullptr, nullptr, texW, texH);
}

void misc::SdlWrapper::spriteRender()
{
    SDL_RenderCopy(this->_renderer.get(), this->_texture.get(), &this->_srcRect, &this->_dstRect);
}

void misc::SdlWrapper::textRender()
{
    SDL_RenderCopy(this->_renderer.get(), this->_textTexture.get(), nullptr, &this->_dstRect);
}

void misc::SdlWrapper::clear()
{
	SDL_RenderClear(this->_renderer.get());
}

void misc::SdlWrapper::display()
{
	SDL_RenderPresent(this->_renderer.get());
}

void misc::SdlWrapper::getEvents(std::queue<arcade::resources::Keys> &events)
{
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_WINDOWEVENT_CLOSE || event.type == SDL_QUIT) {
            events.push(arcade::resources::Keys::Close);
            break;
        }
        if (event.type == SDL_KEYDOWN) {
            const auto evt = arcade::resources::FROM_SDL.find(event.key.keysym.sym);
            if (evt != arcade::resources::FROM_SDL.end())
                events.push(evt->second);
        }
    }
}

SDL_Surface *misc::SdlWrapper::getTextSurface()
{
    return this->_textSurface.get();
}