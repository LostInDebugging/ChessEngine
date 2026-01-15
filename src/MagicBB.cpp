#include <array>
#include <bit>
#include <cmath>
#include <random>
#include <chrono>

#include "MagicBB.h"

namespace MagicBB {
    std::array<uint64_t, 64> BISHOP_MAGICS;
    std::array<uint64_t, 1ull << INDEX_BITS> BISHOP_MOVETABLE;

    std::array<uint64_t, 64> ROOK_MAGICS;
    std::array<uint64_t, 1ull << INDEX_BITS> ROOK_MOVETABLE;

    uint64_t getRookBlockerMask(int sq) {
        uint64_t mask = 0ull;

        int row = sq / 8;
        int col = sq % 8;

        uint64_t pos = 1ull << sq;

        int left = col;
        while (--left >= 1) {
            mask |= pos >> (col - left);
        }

        int right = col;
        while (++right < 7) {
            mask |= pos << (right - col);
        }

        int up = row;
        while (++up < 7) {
            mask |= pos << (8 * (up - row));
        }

        int down = row;
        while (--down >= 1) {
            mask |= pos >> (8 * (row - down));
        }

        return mask;
    }

    uint64_t getBishopBlockerMask(int sq) {
        uint64_t mask = 0ull;

        int row = sq / 8;
        int col = sq % 8;

        uint64_t pos = 1ull << sq;

        // tr
        for (int i = 1; row + i < 7 && col + i < 7; i++) {
            mask |= pos << (9 * i);
        }

        // tl 
        for (int i = 1; row + i < 7 && col - i > 0; i++) {
            mask |= pos << (7 * i);
        }

        // br
        for (int i = 1; row - i > 0 && col + i < 7; i++) {
            mask |= pos >> (7 * i);
        }

        // bl
        for (int i = 1; row - i > 0 && col - i > 0; i++) {
            mask |= pos >> (9 * i);
        }

        return mask;
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

    uint64_t validRookMoves(int sq, uint64_t blockers) {
        int row = sq / 8;
        int col = sq % 8;

        uint64_t pos = 1ull << sq;
        uint64_t validMoves = 0ull;
        for (int left = col - 1; left >= 0; left--) {
            uint64_t move = pos >> (col - left);
            validMoves |= move;
            if ((move & blockers) != 0) break;
        }

        for (int right = col + 1; right < 8; right++) {
            uint64_t move = pos << (right - col);
            validMoves |= move;
            if ((move & blockers) != 0) break;
        }

        for (int up = row + 1; up < 8; up++) {
            uint64_t move = pos << ((up - row) * 8);
            validMoves |= move;
            if ((move & blockers) != 0) break;
        }

        for (int down = row - 1; down >= 0; down--) {
            uint64_t move = pos >> ((row - down) * 8);
            validMoves |= move;
            if ((move & blockers) != 0) break;
        }

        return validMoves;
    }
    
    uint64_t validBishopMoves(int sq, uint64_t blockers) {
        int row = sq / 8;
        int col = sq % 8;

        uint64_t pos = 1ull << sq;
        uint64_t validMoves = 0ull;

        // tr
        for (int i = 1; row + i < 8 && col + i < 8; i++) {
            uint64_t move = pos << (9 * i);
            validMoves |= move;
            if ((move & blockers) != 0) break;
        }

        // tl 
        for (int i = 1; row + i < 8 && col - i >= 0; i++) {
            uint64_t move = pos << (7 * i);
            validMoves |= move;
            if ((move & blockers) != 0) break;
        }

        // br
        for (int i = 1; row - i >= 0 && col + i < 8; i++) {
            uint64_t move = pos >> (7 * i);
            validMoves |= move;
            if ((move & blockers) != 0) break;
        }

        // bl
        for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
            uint64_t move = pos >> (9 * i);
            validMoves |= move;
            if ((move & blockers) != 0) break;
        }

        return validMoves;
    }

    int magicIndex(uint64_t blockers, uint64_t magic) {
        return (blockers * magic) >> (64 - INDEX_BITS);
    }

    uint64_t gen64Random() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::mt19937 mt(seed);

        // 3. Define the distribution (e.g., uniform integer distribution)
        std::uniform_int_distribution<uint64_t> dist(1, ~(0ull));

        // 4. Generate the random number
        return dist(mt);
    }

    bool tryMakeRookTable(int sq, uint64_t magic, std::array<uint64_t, 1ull << INDEX_BITS>& moveTable) {
        uint64_t mask = getRookBlockerMask(sq);
        constexpr uint64_t EMPTY_ENTRY = ~(0ull);
        moveTable.fill(EMPTY_ENTRY);

        for (uint64_t blockers : bitSubsets(mask)) {
            uint64_t moves = validRookMoves(sq, blockers);
            uint64_t *tableEntry = &moveTable[magicIndex(blockers, magic)];
            if (*tableEntry == EMPTY_ENTRY) {
                *tableEntry = moves;
            } else if (*tableEntry != moves) {
                return false;
            }
        }
        return true;
    }

    bool tryMakeBishopTable(int sq, uint64_t magic, std::array<uint64_t, 1ull << INDEX_BITS>& moveTable) {
        uint64_t mask = getBishopBlockerMask(sq);
        constexpr uint64_t EMPTY_ENTRY = ~(0ull);
        moveTable.fill(EMPTY_ENTRY);

        for (uint64_t blockers : bitSubsets(mask)) {
            uint64_t moves = validBishopMoves(sq, blockers);
            uint64_t *tableEntry = &moveTable[magicIndex(blockers, magic)];
            if (*tableEntry == EMPTY_ENTRY) {
                *tableEntry = moves;
            } else if (*tableEntry != moves) {
                return false;
            }
        }
        return true;
    }

    void findRookMagics() {
        for (int sq = 0; sq < 64; sq++) {
            bool foundMagic = false;
            uint64_t magic = 0;
            while (!foundMagic) {
                magic = gen64Random() & gen64Random() & gen64Random();

                foundMagic = tryMakeRookTable(sq, magic, ROOK_MOVETABLE);
            }
            
            ROOK_MAGICS[sq] = magic;
        }
    }

    void findBishopMagics() {
        for (int sq = 0; sq < 64; sq++) {
            bool foundMagic = false;
            uint64_t magic = 0;
            while (!foundMagic) {
                magic = gen64Random() & gen64Random() & gen64Random();

                foundMagic = tryMakeBishopTable(sq, magic, BISHOP_MOVETABLE);
            }
            
            BISHOP_MAGICS[sq] = magic;
        }
    }
}
