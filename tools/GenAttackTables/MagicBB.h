#ifndef MAGICBB_H
#define MAGICBB_H

#include <cstdint>
#include <vector>
#include "Magic.h"

#include "BoardConstants.h"

namespace Magic {
    //
    uint64_t getBlockerMask(int sq, const Direction* dirs, int nDirs);

    //
    std::vector<uint64_t> bitSubsets(uint64_t bitset);

    //
    uint64_t validSliderMoves(int sq, uint64_t blockers, const Direction* dirs, int nDirs);

    //
    uint64_t gen64Random();

    //
    bool tryFillTable(int sq, uint64_t magic, Slider slider);

    //
    std::array<uint64_t, 64> findRookMagics();

    //
    std::array<uint64_t, 64> findBishopMagics();
}

#endif