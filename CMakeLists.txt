cmake_minimum_required(VERSION 3.27)
project(Tetriste)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies

## Raylib
set(RAYLIB_VERSION 5.0)
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
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

## Flecs
find_package(flecs 3.2.11 QUIET)
if (NOT flecs_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            flecs
            URL https://github.com/SanderMertens/flecs/archive/refs/tags/v3.2.11.tar.gz
    )
    FetchContent_MakeAvailable(flecs)
endif()

## JSON Library
find_package(nlohmann_json 3.11.3 QUIET)
if (NOT nlohmann_json_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            nlohmann_json
            URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

# Our Project

add_executable(${PROJECT_NAME} main.cpp
        src/headers/enums.h
        src/headers/constants.h
        src/headers/libs.h
        src/headers/Header.h
        src/utils/ResourceManager.cpp
        src/GameCycle.h
        src/core/RenderModule.h
        src/Scenes/Scene.h
        src/Scenes/NewGame.h
        src/Scenes/ModeScene.h
        src/Scenes/ModeScene.cpp
        src/Scenes/NewGame.cpp
        src/core/TransformModule.h
        src/core/InputModule.h
        src/core/UiModule.h
        src/core/MatchModule.h
        src/core/MatchModule.h
        src/Match-3/Board.h
        src/Match-3/Gem.h
        src/Match-3/Slot.h
        src/Match-3/Button.h
        src/Match-3/Inventory.h
        src/Match-3/Previewer.h
        src/Match-3/LinkedList.h
        src/core/AnimationModule.h
        src/Match-3/Background.h
        src/core/AnimationModule.cpp
        src/Match-3/Label.h
        src/Match-3/Label.h
        src/core/RenderModule.cpp
        src/core/TransformModule.cpp
        src/core/UiModule.cpp
        src/Scenes/TitleScene.cpp
        src/Scenes/TitleScene.h
        src/Scenes/Leaderboard.cpp
        src/Scenes/Leaderboard.h
        src/Scenes/LoadGame.cpp
        src/Scenes/LoadGame.h
        src/Match-3/Session.h
        src/Match-3/Entity.h

)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} flecs::flecs_static)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
