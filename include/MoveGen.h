#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <iostream>
#include <vector>
#include <bit>
#include <array>
#include "Move.h"
#include "GameState.h"

namespace attackTable {
    constexpr std::array<uint64_t, 64> generateKnightAttackTable() {
        std::array<uint64_t, 64> knightAttacks {};

        for (int sq = 0; sq < 64; sq++) {
            uint64_t pos = 1ull << sq;

            knightAttacks[sq] = 
            ((pos << 17) & ~Rays::FILE_A) | // 2 up 1 right
            ((pos << 15) & ~Rays::FILE_H) | // 2 up 1 left
            ((pos << 10) & ~(Rays::FILE_A | Rays::FILE_B)) | // 1 up 2 right
            ((pos << 6) & ~(Rays::FILE_G | Rays::FILE_H)) | // 1 up 2 left
            ((pos >> 17) & ~Rays::FILE_H) | // 2 down 1 left
            ((pos >> 15) & ~Rays::FILE_A) | // 2 down 1 right
            ((pos >> 10) & ~(Rays::FILE_G | Rays::FILE_H)) | // 1 down 2 left
            ((pos >> 6) & ~(Rays::FILE_A | Rays::FILE_B));
        }

        return knightAttacks;
    }

    constexpr std::array<uint64_t, 64> knightAttacks = generateKnightAttackTable();
}

enum class MoveFlag {
    QUIET,
    CAPTURE,
    PROMOTION
};

class MoveGen {
public:
    // generates all single and double pawn pushes. Does not generate promotion moves
    static std::vector<Move> generatePawnPushes(GameState state);

    // generates all pawn promotion moves.
    static std::vector<Move> generatePawnPromotions(GameState g);

    // generates all pawn captures. Also generates promotion captures
    static std::vector<Move> generatePawnCaptures(GameState g);

    // generates all knight moves.
    static std::vector<Move> generateKnightMoves(GameState g);

private:
    static void extractMoves(std::vector<Move>& moves, uint64_t bb, int offset, PieceType moving, MoveFlag flags);
    static void addPromotionMoves(std::vector<Move>& moves, uint64_t bb, int offset);
};

#endif
