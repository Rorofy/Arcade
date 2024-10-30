add_library(
        solarfox SHARED
        main.cpp
        src/SolarFox.cpp
)

set_target_properties(
        solarfox
        PROPERTIES
        PREFIX "arcade_"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib"
)
