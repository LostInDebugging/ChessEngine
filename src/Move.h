#include <iostream>
#include <cstdint>
#include "PieceType.h"
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
    int from;
    int to;
    PieceType movePiece;
    PieceType capture;
    PieceType Promotion;
    int EnPassant;
    int Castling;
public:

};
