#include "MoveGen.h"

std::vector<Move> MoveGen::generateSinglePawnPushes(GameState state) {
    const uint64_t *posBB = state.getPosBB();
    PlayerColour activeColour = state.getActiveColour();

    std::vector<Move> moves;
    if (activeColour == WHITE) {
        uint64_t singlePushes = ((posBB[WHITEPAWNS] & ~Rays::RANKS[7]) << 8) & posBB[EMPTY];
        extractMoves(moves, singlePushes, -8);
        uint64_t doublePushes = ((singlePushes & Rays::RANKS[2]) << 8) & posBB[EMPTY];
        extractMoves(moves, doublePushes, -16);
    }

    return moves;
}

void MoveGen::extractMoves(std::vector<Move>& moves, uint64_t bb, int offset) {
    while (bb != 0) {
        int to = std::countr_zero(bb);
        int from = to + offset;
        bb &= ~(1ull << to);

        moves.push_back(Move(from, to, PAWN, PAWN, PAWN, -1, -1));
    }
}
