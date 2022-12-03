cmake_minimum_required (VERSION 3.8)

project(HammurabiGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
    main.cpp
    EGameResult.h
    GameConditions.h
    GamePlay.hpp
    GamePlay.cpp
    Loader.hpp
    Loader.cpp
    Random.h
    TextMessages.hpp
    TextMessages.cpp
)