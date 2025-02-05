cmake_minimum_required(VERSION 3.27)
project(MonkeyTyper)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.1
)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(fmt)


add_executable(MonkeyTyper main.cpp
        Settings.cpp
        Settings.h
        Game.cpp
        Game.h
        AssetManager.cpp
        Shape.h
        Leaderboards.cpp
        Leaderboards.h
        Savings.cpp
        Savings.h)
target_link_libraries(MonkeyTyper sfml-graphics)
target_link_libraries(MonkeyTyper sfml-audio)
target_link_libraries(MonkeyTyper fmt)