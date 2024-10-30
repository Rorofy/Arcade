add_library(
        nibbler SHARED
        main.cpp
        src/Nibbler.cpp
        src/Snake.cpp
        ../../src/resources/Color.cpp
        src/Snake.cpp include/Snake.hpp include/misc/Direction.hpp)

set_target_properties(
        nibbler
        PROPERTIES
        PREFIX "arcade_"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
)