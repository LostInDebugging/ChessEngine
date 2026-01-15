#include <array>
#include <bit>
#include <cmath>
#include <random>
#include <chrono>
#include <iostream>

#include "MagicBB.h"
#include "Precompute.h"

namespace MagicBB {
    struct Direction { 
        int dr; 
        int dc; 
    };

    constexpr Direction ROOK_DIRS[] = {
        { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }
    };

    constexpr Direction BISHOP_DIRS[] = {
        { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 }
    };

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

    uint64_t getBlockerMask(int sq, const Direction* dirs, int nDirs) {
        int r = sq / 8;
        int c = sq % 8;
        uint64_t mask = 0;

        for (int d = 0; d < nDirs; d++) {
            int rr = r + dirs[d].dr;
            int cc = c + dirs[d].dc;

            while (rr > 0 && rr < 7 && cc > 0 && cc < 7) {
                mask |= 1ULL << (rr * 8 + cc);
                rr += dirs[d].dr;
                cc += dirs[d].dc;
            }
        }
        return mask;
    }

    uint64_t validSliderMoves(int sq, uint64_t blockers, const Direction* dirs, int nDirs) {
        int r = sq >> 3;
        int c = sq & 7;
        uint64_t moves = 0;

        for (int d = 0; d < nDirs; d++) {
            int rr = r + dirs[d].dr;
            int cc = c + dirs[d].dc;

            while (rr >= 0 && rr < 8 && cc >= 0 && cc < 8) {
                uint64_t bit = 1ULL << (rr * 8 + cc);
                moves |= bit;
                if (blockers & bit) break;
                rr += dirs[d].dr;
                cc += dirs[d].dc;
            }
        }
        return moves;
    }

    std::vector<uint64_t> bitSubsets(uint64_t bitset) {
        std::vector<uint64_t> subsets;

        uint64_t subset = 0ull;

        while (true) {
            // Carry-Ripler trick to iterate through subsets
            subset |= ~bitset;
            subset += 1;
            subset &= bitset;


            subsets.push_back(subset);

            if (subset == 0ull) {
                break;
            }
        }

        return subsets;
    }

    int magicIndex(int sq, uint64_t blockers, uint64_t magic, Slider slider) {
        return (blockers * magic) >> (64 - slider.indexBits[sq]);
    }
    
    uint64_t gen64Random() {
        // Seed and RNG are static, so this block runs only once
        static unsigned long long seed = std::random_device{}(); // generate seed once
        static std::mt19937_64 rng(seed);                       // initialize RNG once
        static bool printed = false;                            

        // Print the seed only the first time
        if (!printed) {
            std::cout << "Seed used: " << seed << '\n';
            printed = true;
        }

        return rng(); // generate next random number
    }

    bool tryFillTable(int sq, uint64_t magic, Slider slider) {
        constexpr uint64_t EMPTY_ENTRY = ~(0ull);
        std::vector<uint64_t> moveTable(1ull << slider.indexBits[sq], EMPTY_ENTRY);

        uint64_t mask = getBlockerMask(sq, slider.dirs, slider.dirCount);

        for (uint64_t blockers : bitSubsets(mask)) {
            uint64_t moves = validSliderMoves(sq, blockers, slider.dirs, slider.dirCount);
            uint64_t *tableEntry = &moveTable[magicIndex(sq, blockers, magic, slider)];
            if (*tableEntry == EMPTY_ENTRY) {
                *tableEntry = moves;
            } else if (*tableEntry != moves) {
                return false;
            }
        }
        return true;
    }

    std::array<uint64_t, 64> findRookMagics() {
        std::array<uint64_t, 64> rookMagics;
        for (int sq = 0; sq < 64; sq++) {
            bool foundMagic = false;
            uint64_t magic = 0;
            while (!foundMagic) {
                magic = gen64Random() & gen64Random() & gen64Random();

                foundMagic = tryFillTable(sq, magic, ROOK);
            }
            
            rookMagics[sq] = magic;
        }

        return rookMagics;
    }

    std::array<uint64_t, 64> findBishopMagics() {
        std::array<uint64_t, 64> bishopMagics;
        for (int sq = 0; sq < 64; sq++) {
            bool foundMagic = false;
            uint64_t magic = 0;
            while (!foundMagic) {
                magic = gen64Random() & gen64Random() & gen64Random();

                foundMagic = tryFillTable(sq, magic, BISHOP);
            }
            
            bishopMagics[sq] = magic;
        }

        return bishopMagics;
    }

    std::array<uint64_t, 1ull << 12> populateBishopAttackTable() {
        std::array<uint64_t, 1ull << 12> bishopAttackTable;
        for (int sq = 0; sq < 64; sq++) {
            uint64_t magic = BISHOP_MAGICS[sq];
            uint64_t mask = BISHOP_BLOCKER_MASKS[sq];

            for (uint64_t blockers : bitSubsets(mask)) {
                int mi = magicIndex(sq, blockers, magic, BISHOP);
                uint64_t moves = validSliderMoves(sq, blockers, BISHOP.dirs, BISHOP.dirCount);
                bishopAttackTable[mi] = moves;
            }
        }

        return bishopAttackTable;
    }

    std::array<uint64_t, 1ull << 12> populateRookAttackTable() {
        std::array<uint64_t, 1ull << 12> rookAttackTable;
        for (int sq = 0; sq < 64; sq++) {
            uint64_t magic = ROOK_MAGICS[sq];
            uint64_t mask = ROOK_BLOCKER_MASKS[sq];

            for (uint64_t blockers : bitSubsets(mask)) {
                int mi = magicIndex(sq, blockers, magic, ROOK);
                uint64_t moves = validSliderMoves(sq, blockers, ROOK.dirs, ROOK.dirCount);
                rookAttackTable[mi] = moves;
            }
        }

        return rookAttackTable;
    }
}
