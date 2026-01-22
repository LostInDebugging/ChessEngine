#include <bit>
#include "Attacks.h"
#include "MoveGen.h"
#include "Helpers.h"

//TODO CHECK SQAURES BETWEEN KING AND ROOK
std::vector<Move> MoveGen::generateCastlingMoves(GameState g) {
    std::vector<Move> moves;

    PlayerColour activeColour = g.getActiveColour();
    uint64_t myPieces = g.pieceBB({PieceType::INVALID, activeColour});

    int castlingRights = g.getCastlingRights();
    if ((castlingRights & WHITE_KINGSIDE) && !(myPieces & WHITE_KINGSIDE_BLOCKERS)) {
        moves.push_back(Move(-1, -1, PieceType::INVALID, PieceType::INVALID, -1, WHITE_KINGSIDE));
    }
    if ((castlingRights & WHITE_QUEENSIDE) && !(myPieces & WHITE_QUEENSIDE_BLOCKERS)) {
        moves.push_back(Move(-1, -1, PieceType::INVALID, PieceType::INVALID, -1, WHITE_QUEENSIDE));
    }
    if ((castlingRights & BLACK_KINGSIDE)  && !(myPieces & BLACK_KINGSIDE_BLOCKERS)) {
        moves.push_back(Move(-1, -1, PieceType::INVALID, PieceType::INVALID, -1, BLACK_KINGSIDE));
    }
    if ((castlingRights & BLACK_QUEENSIDE) && !(myPieces & BLACK_QUEENSIDE_BLOCKERS)) {
        moves.push_back(Move(-1, -1, PieceType::INVALID, PieceType::INVALID, -1, BLACK_QUEENSIDE));
    }

    return moves;
}

//TODO AVOID WRAPAROUND
std::vector<Move> MoveGen::generateEnPassant(GameState g) {
    std::vector<Move> moves;

    int sq = g.getEnPassant();
    int sqBB = 1ull << sq;

    if (sq == NO_EN_PASSANT) {
        return std::vector<Move>();
    }

    PlayerColour activeColour = g.getActiveColour();
    uint64_t myPawns = g.pieceBB({PieceType::PAWN, activeColour});

    if (activeColour == PlayerColour::WHITE) {
        uint64_t fromPawns = myPawns & ((sqBB >> 7) | (sqBB >> 9));
        while (fromPawns != 0) {
            int from = std::countr_zero(fromPawns);
            fromPawns &= ~(1ull << from);

            moves.push_back(Move(from, sq, PieceType::PAWN, PieceType::INVALID, sq, -1));
        }
    } else {
        uint64_t fromPawns = myPawns & ((sqBB << 7) | (sqBB << 9));
        while (fromPawns != 0) {
            int from = std::countr_zero(fromPawns);
            fromPawns &= ~(1ull << from);

            moves.push_back(Move(from, sq, PieceType::PAWN, PieceType::INVALID, sq, -1));
        }
    }

    return moves;
}

std::vector<Move> MoveGen::generateBishopMoves(GameState g) {
    std::vector<Move> moves;

    PlayerColour activeColour = g.getActiveColour();
    uint64_t ourBB = g.pieceBB({PieceType::INVALID, activeColour});
    uint64_t bishopsBB = g.pieceBB({PieceType::BISHOP, activeColour});

    while (bishopsBB != 0) {
        int from = std::countr_zero(bishopsBB);
        bishopsBB &= ~(1ull << from);

        uint64_t blockers = Magic::BISHOP_BLOCKER_MASKS[from] & ourBB;
        uint64_t magic = Magic::BISHOP_MAGICS[from];
        uint64_t bishopMovesBB = Attacks::bishopAttacks[Magic::magicIndex(from, blockers, magic, Magic::BISHOP)];
        bishopMovesBB &= ~ourBB;

        while (bishopMovesBB != 0) {
            int to = std::countr_zero(bishopMovesBB);
            bishopMovesBB &= ~(1ull << to);

            moves.push_back(Move(from, to, PieceType::BISHOP, PieceType::INVALID, -1, -1));
        }
    }
    return moves;
}

std::vector<Move> MoveGen::generateRookMoves(GameState g) {
    std::vector<Move> moves;

    PlayerColour activeColour = g.getActiveColour();
    uint64_t ourBB = g.pieceBB({PieceType::INVALID, activeColour});
    uint64_t rooksBB = g.pieceBB({PieceType::ROOK, activeColour});

    while (rooksBB != 0) {
        int from = std::countr_zero(rooksBB);
        rooksBB &= ~(1ull << from);

        uint64_t blockers = Magic::ROOK_BLOCKER_MASKS[from] & ourBB;
        uint64_t magic = Magic::ROOK_MAGICS[from];
        uint64_t rookMovesBB = Attacks::rookAttacks[Magic::magicIndex(from, blockers, magic, Magic::ROOK)];
        rookMovesBB &= ~ourBB;
        while (rookMovesBB != 0) {
            int to = std::countr_zero(rookMovesBB);
            rookMovesBB &= ~(1ull << to);

            moves.push_back(Move(from, to, PieceType::ROOK, PieceType::INVALID, -1, -1));
        }
    }
    return moves;
}

std::vector<Move> MoveGen::generateQueenMoves(GameState g) {
    std::vector<Move> moves;

    PlayerColour activeColour = g.getActiveColour();
    uint64_t ourBB = g.pieceBB({PieceType::INVALID, activeColour});
    uint64_t queensBB = g.pieceBB({PieceType::QUEEN, activeColour});

    while (queensBB != 0) {
        int from = std::countr_zero(queensBB);
        queensBB &= ~(1ull << from);

        // Rook-like moves
        uint64_t rookBlockers = Magic::ROOK_BLOCKER_MASKS[from] & ourBB;
        uint64_t rookMagic = Magic::ROOK_MAGICS[from];
        uint64_t rookMovesBB = Attacks::rookAttacks[Magic::magicIndex(from, rookBlockers, rookMagic, Magic::ROOK)];

        // Bishop-like moves
        uint64_t bishopBlockers = Magic::BISHOP_BLOCKER_MASKS[from] & ourBB;
        uint64_t bishopMagic = Magic::BISHOP_MAGICS[from];
        uint64_t bishopMovesBB = Attacks::bishopAttacks[Magic::magicIndex(from, bishopBlockers, bishopMagic, Magic::BISHOP)];

        uint64_t queenMovesBB = (rookMovesBB | bishopMovesBB) & ~ourBB;

        while (queenMovesBB != 0) {
            int to = std::countr_zero(queenMovesBB);
            queenMovesBB &= ~(1ull << to);

            moves.push_back(Move(from, to, PieceType::QUEEN, PieceType::INVALID, -1, -1));
        }
    }
    return moves;
}

std::vector<Move> MoveGen::generateKingMoves(GameState g) {
    std::vector<Move> moves;

    PlayerColour activeColour = g.getActiveColour();
    uint64_t kingsBB = g.pieceBB({PieceType::KING, activeColour});

    while (kingsBB != 0) {
        int from = std::countr_zero(kingsBB);
        kingsBB &= ~(1ull << from);

        uint64_t kingMovesBB = (Attacks::kingAttacks[from] & ~g.pieceBB({PieceType::INVALID, activeColour}));

        while (kingMovesBB != 0) {
            int to = std::countr_zero(kingMovesBB);
            kingMovesBB &= ~(1ull << to);

            moves.push_back(Move(from, to, PieceType::KING, PieceType::INVALID, -1, -1));
        }
    }

    return moves;
}

std::vector<Move> MoveGen::generateKnightMoves(GameState g) {
    std::vector<Move> moves;

    PlayerColour activeColour = g.getActiveColour();
    uint64_t knightsBB = g.pieceBB({PieceType::KNIGHT, activeColour});

    while (knightsBB != 0) {
        int from = std::countr_zero(knightsBB);
        knightsBB &= ~(1ull << from);

        uint64_t knightMovesBB = (Attacks::knightAttacks[from] & ~g.pieceBB({PieceType::INVALID, activeColour}));

        while (knightMovesBB != 0) {
            int to = std::countr_zero(knightMovesBB);
            knightMovesBB &= ~(1ull << to);

            moves.push_back(Move(from, to, PieceType::KNIGHT, PieceType::INVALID, -1, -1));
        }
    }

    return moves;
}

//TODO AVOID WRAPAROUND
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

//TODO AVOID WRAPAROUND
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
