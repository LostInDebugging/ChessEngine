#include <array>
#include <bit>
#include <cmath>
#include <random>
#include <chrono>
#include <iostream>

#include "MagicBB.h"
#include "Magic.h"
#include "BoardConstants.h"

namespace Magic {
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


}
