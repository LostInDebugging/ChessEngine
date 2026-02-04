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
    static std::vector<Move> generatePawnPushes(std::vector<Move> moves, GameState state);

    // generates all pawn promotion moves.
    static std::vector<Move> generatePawnPromotions(std::vector<Move> moves, GameState g);

    // generates all pawn captures. Also generates promotion captures
    static std::vector<Move> generatePawnCaptures(std::vector<Move> moves, GameState g);

    // generates En Passant move if possible.
    static std::vector<Move> generateEnPassant(std::vector<Move> moves, GameState g);

    // generates all knight moves.
    static std::vector<Move> generateKnightMoves(std::vector<Move> moves, GameState g);

    // generates all bishop moves.
    static std::vector<Move> generateBishopMoves(std::vector<Move> moves, GameState g);

    // generates all rook moves.
    static std::vector<Move> generateRookMoves(std::vector<Move> moves, GameState g);

    // generates all queen moves.
    static std::vector<Move> generateQueenMoves(std::vector<Move> moves, GameState g);

    // generates all king moves.
    static std::vector<Move> generateKingMoves(std::vector<Move> moves, GameState g);

    // generates all castling moves.
    static std::vector<Move> generateCastlingMoves(std::vector<Move> moves, GameState g);

    // generates all pseudolegal moves.
    static std::vector<Move> generatePseudolegalMoves(GameState g);
private:
    static void extractMoves(std::vector<Move>& moves, uint64_t bb, int offset, PieceType moving, MoveFlag flags);
    static void addPromotionMoves(std::vector<Move>& moves, uint64_t bb, int offset);
};

#endif
