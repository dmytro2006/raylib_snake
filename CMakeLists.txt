cmake_minimum_required(VERSION 3.28)
project(raylib_snake)

set(CMAKE_CXX_STANDARD 14)

# static linking
if(WINDOWS)
    set(CMAKE_CXX_FLAGS "-static")
endif ()

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    endif ()
endif ()

add_executable(raylib_snake
        src/main.cpp
        src/snake.cpp
        src/fruit.cpp
        src/ui.cpp
        src/game.cpp
)

target_include_directories(raylib_snake PUBLIC include)

target_link_libraries(raylib_snake PUBLIC raylib)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()
