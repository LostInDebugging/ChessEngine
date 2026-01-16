#include <bit>
#include "MoveGen.h"
#include "attackTables.h"
#include "Helpers.h"

std::vector<Move> MoveGen::generateKnightMoves(GameState g) {
    std::vector<Move> moves;

    PlayerColour activeColour = g.getActiveColour();
    uint64_t knightsBB = g.pieceBB({PieceType::KNIGHT, activeColour});

    while (knightsBB != 0) {
        int from = std::countr_zero(knightsBB);
        knightsBB &= ~(1ull << from);

        uint64_t knightMovesBB = (attackTables::knightAttacks[from] & ~g.pieceBB({PieceType::INVALID, activeColour}));

        while (knightMovesBB != 0) {
            int to = std::countr_zero(knightMovesBB);
            knightMovesBB &= ~(1ull << to);

            moves.push_back(Move(from, to, PieceType::KNIGHT, PieceType::INVALID, -1, -1));
        }
    }

    return moves;
}

std::vector<Move> MoveGen::generatePawnCaptures(GameState g) {
    PlayerColour activeColour = g.getActiveColour();

    std::vector<Move> moves;
    if (activeColour == PlayerColour::WHITE) {
        uint64_t rightCaptures = (g.pieceBB({PieceType::PAWN, activeColour}) << 9) & g.pieceBB({PieceType::INVALID, PlayerColour::BLACK});
        uint64_t leftCaptures = (g.pieceBB({PieceType::PAWN, activeColour}) << 7) & g.pieceBB({PieceType::INVALID, PlayerColour::BLACK});

        addPromotionMoves(moves, rightCaptures & Rays::RANK_8, -9);
        addPromotionMoves(moves, leftCaptures & Rays::RANK_8, -7);
        extractMoves(moves, rightCaptures & ~Rays::RANK_8, -9, PieceType::PAWN, MoveFlag::CAPTURE);
        extractMoves(moves, rightCaptures & ~Rays::RANK_8, -7, PieceType::PAWN, MoveFlag::CAPTURE);
    } else if (activeColour == PlayerColour::BLACK) {
        uint64_t rightCaptures = (g.pieceBB({PieceType::PAWN, activeColour}) >> 7) & g.pieceBB({PieceType::INVALID, PlayerColour::WHITE});
        uint64_t leftCaptures = (g.pieceBB({PieceType::PAWN, activeColour}) >> 9) & g.pieceBB({PieceType::INVALID, PlayerColour::WHITE});
        uint64_t allCaptures = rightCaptures | leftCaptures;

        addPromotionMoves(moves, rightCaptures & Rays::RANK_1, 7);
        addPromotionMoves(moves, leftCaptures & Rays::RANK_1, 9);
        extractMoves(moves, rightCaptures & ~Rays::RANK_1, 7, PieceType::PAWN, MoveFlag::CAPTURE);
        extractMoves(moves, rightCaptures & ~Rays::RANK_1, 9, PieceType::PAWN, MoveFlag::CAPTURE);
    }

    return moves;
}

std::vector<Move> MoveGen::generatePawnPushes(GameState g) {
    PlayerColour activeColour = g.getActiveColour();

    std::vector<Move> moves;
    if (activeColour == PlayerColour::WHITE) {
        uint64_t singlePushes = ((g.pieceBB({PieceType::PAWN, activeColour}) & ~Rays::RANK_7) << 8) & g.getEmptyBB();
        extractMoves(moves, singlePushes, -8, PieceType::PAWN, MoveFlag::QUIET);
        uint64_t doublePushes = ((singlePushes & Rays::RANK_3) << 8) & g.getEmptyBB();
        extractMoves(moves, singlePushes, -16, PieceType::PAWN, MoveFlag::QUIET);
    } else if (activeColour == PlayerColour::BLACK) {
        uint64_t singlePushes = ((g.pieceBB({PieceType::PAWN, activeColour}) & ~Rays::RANK_2) >> 8) & g.getEmptyBB();
        extractMoves(moves, singlePushes, 8, PieceType::PAWN, MoveFlag::QUIET);
        uint64_t doublePushes = ((singlePushes & Rays::RANK_6) >> 8) & g.getEmptyBB();
        extractMoves(moves, singlePushes, 16, PieceType::PAWN, MoveFlag::QUIET);
    }

    return moves;
}

std::vector<Move> MoveGen::generatePawnPromotions(GameState g) {
    PlayerColour activeColour = g.getActiveColour();

    std::vector<Move> moves;
    if (activeColour == PlayerColour::WHITE) {
        uint64_t promoMoves = ((g.pieceBB({PieceType::PAWN, activeColour}) & Rays::RANK_7) << 8) & g.getEmptyBB();
        addPromotionMoves(moves, promoMoves, -8);
    } else if (activeColour == PlayerColour::BLACK) {
        uint64_t promoMoves = ((g.pieceBB({PieceType::PAWN, activeColour}) & Rays::RANK_2) >> 8) & g.getEmptyBB();
        addPromotionMoves(moves, promoMoves, 8);
    }

    return moves;
}   

void MoveGen::addPromotionMoves(std::vector<Move>& moves, uint64_t bb, int offset) {
    while (bb != 0) {
        int to = std::countr_zero(bb);
        int from = to + offset;
        bb &= ~(1ull << to);

        moves.push_back(Move(from, to, PieceType::PAWN, PieceType::KNIGHT, -1, -1));
        moves.push_back(Move(from, to, PieceType::PAWN, PieceType::BISHOP, -1, -1));
        moves.push_back(Move(from, to, PieceType::PAWN, PieceType::ROOK, -1, -1));
        moves.push_back(Move(from, to, PieceType::PAWN, PieceType::QUEEN, -1, -1));
    }
}

void MoveGen::extractMoves(std::vector<Move>& moves, uint64_t bb, int offset, PieceType moving, MoveFlag flags) {
    while (bb != 0) {
        int to = std::countr_zero(bb);
        int from = to + offset;
        bb &= ~(1ull << to);

        moves.push_back(Move(from, to, moving, PieceType::INVALID, -1, -1));
    }
}
