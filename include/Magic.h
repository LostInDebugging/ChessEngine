#ifndef MAGIC_H
#define MAGIC_H

#include <array>
#include <cstdint>

#include "BoardConstants.h"

namespace Magic {
    constexpr int MAX_ROOK_TABLE_SIZE = 1ull << 12;
    constexpr int MAX_BISHOP_TABLE_SIZE = 1ull << 9;


    struct Slider {
        const Direction* dirs;
        int dirCount;
        const int *indexBits;
    };

    const int ROOK_BITS[64] = {
        12, 11, 11, 11, 11, 11, 11, 12,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        11, 10, 10, 10, 10, 10, 10, 11,
        12, 11, 11, 11, 11, 11, 11, 12
    };

    const int BISHOP_BITS[64] = {
        6, 5, 5, 5, 5, 5, 5, 6,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 7, 7, 7, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 9, 9, 7, 5, 5,
        5, 5, 7, 7, 7, 7, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 5, 5, 5, 5, 5, 5, 6
    };
    
    constexpr Slider ROOK = { ROOK_DIRS, 4, ROOK_BITS };
    constexpr Slider BISHOP = { BISHOP_DIRS, 4, BISHOP_BITS };

    extern const std::array<uint64_t, 64> BISHOP_MAGICS;
    extern const std::array<uint64_t, 64> ROOK_MAGICS;

    extern const uint64_t ROOK_BLOCKER_MASKS[64];
    extern const uint64_t BISHOP_BLOCKER_MASKS[64];

    int magicIndex(int sq, uint64_t blockers, uint64_t magic, Slider slider);
    uint64_t getBishopMoves(int sq, uint64_t all);
    uint64_t getRookMoves(int sq, uint64_t all);
}

#endif
