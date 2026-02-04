set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_minimum_required(VERSION 3.22)
project(ChessEngine)

# MAIN APPLICATION
#------------------------------------------------
add_executable(app 
    src/main.cpp
    src/GameState.cpp
    src/Move.cpp 
    src/MoveGen.cpp
    src/Helpers.cpp
    src/Magic.cpp

    data/BishopAttacks.cpp
    data/KingAttacks.cpp
    data/KnightAttacks.cpp
    data/RookAttacks.cpp
    data/BishopMagics.cpp
    data/RookMagics.cpp
    data/Blockers.cpp
    
    common/Magic.cpp
)

target_include_directories(app PRIVATE include)
target_include_directories(app PRIVATE tools/GenAttackTables)

# GEN ATTACK TABLES TOOL
#------------------------------------------------
add_executable(gen
    tools/GenAttackTables/MagicBB.cpp
    tools/GenAttackTables/GenBishopAttacks.cpp
    tools/GenAttackTables/GenRookAttacks.cpp
    tools/GenAttackTables/main.cpp
    data/Blockers.cpp
    common/Magic.cpp
)

target_include_directories(gen PRIVATE include)
target_include_directories(gen PRIVATE tools/GenAttackTables)
