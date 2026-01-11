#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <cstdint>
#include <string>
#include "BoardConstants.h"

// MAYBE USEFUL LATER IN A BETTER IMPLEMENTATION OF MOVES.
/*
enum MoveFlag {
    FROM_FLAG = (std::uint16_t)0b111111 << 10,
    TO_FLAG = (std::uint16_t)0b111111 << 4,
    PROMO_FLAG = (std::uint16_t)1 << 3,
    CAPTURE_FLAG = (std::uint16_t)1 << 2,
    SPECIAL1_FLAG = (std::uint16_t)1 << 1,
    SPECIAL2_FLAG = (std::uint16_t)1
};
*/

class Move {
    // std::uint16_t move;
    int m_From;
    int m_To;
    PieceType m_MovePiece;
    PieceType m_Promotion;
    int m_EnPassant;
    int m_Castling;
public:
    Move (int from, int to, PieceType movePiece, 
        PieceType promotion, int enPassant, int castling);
        
    void printMove();

private:
    std::string getPieceName(PieceType piece);
};

#endif
