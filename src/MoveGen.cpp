#include <bit>
#include "MoveGen.h"
#include "Helpers.h"

std::vector<Move> MoveGen::generatePawnPushes(GameState state) {
    const uint64_t *posBB = state.getPosBB();
    PlayerColour activeColour = state.getActiveColour();

    std::vector<Move> moves;
    if (activeColour == PlayerColour::WHITE) {
        uint64_t singlePushes = ((posBB[bbIndex(bbVal::WHITEPAWNS)] & ~Rays::RANKS[7]) << 8) & state.getEmptyBB();
        extractMoves(moves, singlePushes, -8);
        uint64_t doublePushes = ((singlePushes & Rays::RANKS[2]) << 8) & state.getEmptyBB();
        extractMoves(moves, doublePushes, -16);
    }

    return moves;
}

void MoveGen::extractMoves(std::vector<Move>& moves, uint64_t bb, int offset) {
    while (bb != 0) {
        int to = std::countr_zero(bb);
        int from = to + offset;
        bb &= ~(1ull << to);

        moves.push_back(Move(from, to, PieceType::PAWN, PieceType::PAWN, PieceType::PAWN, -1, -1));
    }
}
