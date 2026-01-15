#ifndef MAGICBB_H
#define MAGICBB_H

namespace MagicBB {
    struct Direction;
    struct Slider;

    uint64_t getBlockerMask(int sq, const Direction* dirs, int nDirs);

    std::vector<uint64_t> bitSubsets(uint64_t bitset);

    uint64_t validSliderMoves(int sq, uint64_t blockers, const Direction* dirs, int nDirs);

    int magicIndex(int sq, uint64_t blockers, uint64_t magic, Slider slider);

    uint64_t gen64Random();

    bool tryFillTable(int sq, uint64_t magic, Slider slider);

    std::array<uint64_t, 64> findRookMagics();

    std::array<uint64_t, 64> findBishopMagics();

    std::array<uint64_t, 1ull << 12> populateRookAttackTable();

    std::array<uint64_t, 1ull << 12> populateBishopAttackTable();
}

#endif
