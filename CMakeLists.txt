set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_minimum_required(VERSION 3.22)
project(ChessEngine)
add_executable(app 
    src/main.cpp
    src/GameState.cpp
    src/Move.cpp 
    src/MoveGen.cpp
    src/Helpers.cpp
    src/MagicBB.cpp
)

target_include_directories(app PRIVATE include)
