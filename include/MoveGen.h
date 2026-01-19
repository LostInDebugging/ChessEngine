#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <iostream>
#include <vector>
#include <bit>
#include <array>
#include "Move.h"
#include "GameState.h"

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

    // generates En Passant move if possible.
    static std::vector<Move> generateEnPassant(GameState g);

    // generates all knight moves.
    static std::vector<Move> generateKnightMoves(GameState g);

    // generates all bishop moves.
    static std::vector<Move> generateBishopMoves(GameState g);

    // generates all rook moves.
    static std::vector<Move> generateRookMoves(GameState g);

    // generates all queen moves.
    static std::vector<Move> generateQueenMoves(GameState g);

    // generates all king moves.
    static std::vector<Move> generateKingMoves(GameState g);

    // generates all castling moves.
    static std::vector<Move> generateCastlingMoves(GameState g);
private:
    static void extractMoves(std::vector<Move>& moves, uint64_t bb, int offset, PieceType moving, MoveFlag flags);
    static void addPromotionMoves(std::vector<Move>& moves, uint64_t bb, int offset);
};

#endif
