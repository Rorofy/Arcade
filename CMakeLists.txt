cmake_minimum_required(VERSION 3.17)
project(B_OOP_400_PAR_4_1_arcade_mihailo_pavlovic)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)
find_package(Curses REQUIRED)


include_directories(include)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CONTENT}..)

# ------ ARCADE BINARY ------

add_executable(
        arcade
        main.cpp
        core/src/Core.cpp
        include/misc/DLWrapper.hpp
        src/misc/DLWrapper.cpp
        core/src/Greeter.cpp
        src/resources/Color.cpp
)

target_link_libraries(
        arcade
        dl
)

# ------ SOLARFOX LIBRARY ------

add_subdirectory(games/solarfox)

# ------ NIBBLER LIBRARY ------

add_subdirectory(games/nibbler)

# ------ SFML LIBRARY ------

add_library(
        sfml SHARED
        src/display/sfml/Sfml.cpp
        src/display/sfml/main.cpp
)

set_target_properties(
        sfml
        PROPERTIES
        PREFIX "arcade_"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CONTENT}../lib"
)

target_link_libraries(
        sfml
        sfml-network
        sfml-audio
        sfml-graphics
        sfml-window
        sfml-system
)


# ------ NCURSES LIBRARY ------

add_library(
        ncurses SHARED
        src/display/curses/Curses.cpp
        src/display/curses/main.cpp
        src/resources/Color.cpp
        src/misc/CursesWrapper.cpp
)

target_link_libraries(ncurses ${CURSES_LIBRARIES})
target_include_directories(
        ncurses
        PRIVATE
        ${CURSES_INCLUDE_DIRS}
)

set_target_properties(
        ncurses
        PROPERTIES
        PREFIX "arcade_"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CONTENT}../lib"
)

# ------ SDL2 LIBRARY ------

add_library(
        sdl2 SHARED
        src/display/sdl/Sdl.cpp
        src/display/sdl/main.cpp
        src/misc/SdlWrapper.cpp
)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIR})

target_include_directories(
        sdl2
        PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_DIRS}
        ${SDL2TTF_INCLUDE_DIR}
)
target_link_libraries(
        sdl2
        PRIVATE SDL2::Main
        PRIVATE SDL2::Image
        PRIVATE SDL2::TTF
)

set_target_properties(
        sdl2
        PROPERTIES
        PREFIX "arcade_"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CONTENT}../lib"
)

# ------ PDF MAKE ------

add_custom_target(
        pdf
        COMMAND doxygen ..
        COMMAND make -C ../doc pdf
)
