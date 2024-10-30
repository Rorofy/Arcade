#include <misc/CursesWrapper.hpp>

misc::CursesWrapper::CursesWrapper()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    resizeterm(arcade::TERM_WIDTH, arcade::TERM_HEIGHT);
    curs_set(0);
    start_color();
    use_default_colors();
}

misc::CursesWrapper::~CursesWrapper()
{
    endwin();
}

void misc::CursesWrapper::displayChar(std::uint16_t color, arcade::Coords<int> termCoords, std::uint32_t termChar)
{
    attron(COLOR_PAIR(color));
    mvaddch(termCoords.y, termCoords.x, termChar);
    attroff(COLOR_PAIR(color));
}

void misc::CursesWrapper::displayStr(std::uint16_t color, arcade::Coords<int> termCoords, const std::string& text)
{
    attron(COLOR_PAIR(color));
    mvaddstr(termCoords.y, termCoords.x, text.c_str());
    attroff(COLOR_PAIR(color));
}

void misc::CursesWrapper::wrapperClear()
{
    clear();
}

void misc::CursesWrapper::wrapperRefresh()
{
    refresh();
}

int16_t misc::CursesWrapper::getEvent()
{
    return getch();
}

void misc::CursesWrapper::initColor(short COLOR, short red, short green, short blue)
{
    init_color(COLOR, red, green, blue);
}

void misc::CursesWrapper::initPair(short pair, short color1, short color2)
{
    init_pair(pair, color1, color2);
}