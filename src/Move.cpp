#include "Move.h"
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

Move::Move (int from, int to, PieceType movePiece, PieceType capture, 
    PieceType promotion, int enPassant, int castling) :
    m_From(from), m_To(to), m_MovePiece(movePiece), m_Capture(capture), 
    m_Promotion(promotion), m_EnPassant(enPassant), m_Castling(castling)
{
}

void Move::printMove() {
    std::cout << getPieceName(m_MovePiece) + " from " << m_From << " to " << m_To << "\n";
}

std::string Move::getPieceName(PieceType piece) {
    switch(piece) {
        case PieceType::PAWN:
            return "pawn";
    }
    return "invalid";
}
