#ifndef MAGICBB_H
#define MAGICBB_H

namespace MagicBB {
    constexpr int INDEX_BITS = 12;
    
    extern std::array<uint64_t, 64> BISHOP_MAGICS;
    extern std::array<uint64_t, 1ull << INDEX_BITS> BISHOP_MOVETABLE;

    extern std::array<uint64_t, 64> ROOK_MAGICS;
    extern std::array<uint64_t, 1ull << INDEX_BITS> ROOK_MOVETABLE;

    uint64_t getRookBlockerMask(int sq);

    uint64_t getBishopBlockerMask(int sq);

    std::vector<uint64_t> bitSubsets(uint64_t bitset);

    uint64_t validRookMoves(int sq, uint64_t blockers);

    uint64_t validBishopMoves(int sq, uint64_t blockers);

    int magicIndex(uint64_t blockers, uint64_t magic);

    uint64_t gen64Random();

    bool tryMakeRookTable(int sq, uint64_t magic, std::array<uint64_t, 1ull << INDEX_BITS>& moveTable);

    bool tryMakeBishopTable(int sq, uint64_t magic, std::array<uint64_t, 1ull << INDEX_BITS>& moveTable);

    void findRookMagics();

    void findBishopMagics();
}

#endif
