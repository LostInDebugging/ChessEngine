#include <bit>
#include "MoveGen.h"
#include "Helpers.h"

std::vector<Move> MoveGen::generatePawnPushes(GameState g) {
    PlayerColour activeColour = g.getActiveColour();

    std::vector<Move> moves;
    if (activeColour == PlayerColour::WHITE) {
        uint64_t singlePushes = ((g.pieceBB({PieceType::PAWN, activeColour}) & ~Rays::RANK_7) << 8) & g.getEmptyBB();
        extractMoves(moves, singlePushes, -8);
        uint64_t doublePushes = ((singlePushes & Rays::RANK_3) << 8) & g.getEmptyBB();
        extractMoves(moves, doublePushes, -16);
    } else if (activeColour == PlayerColour::BLACK) {
        uint64_t singlePushes = ((g.pieceBB({PieceType::PAWN, activeColour}) & ~Rays::RANK_2) >> 8) & g.getEmptyBB();
        extractMoves(moves, singlePushes, 8);
        uint64_t doublePushes = ((singlePushes & Rays::RANK_6) >> 8) & g.getEmptyBB();
        extractMoves(moves, doublePushes, 16);
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
