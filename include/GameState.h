#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>

#include <limits>
#include "BoardConstants.h"

enum class castlingRights {
    WHITE_KINGSIDE = 1,
    WHITE_QUEENSIDE = 2,
    BLACK_KINGSIDE = 4,
    BLACK_QUEENSIDE = 8
};

constexpr int NO_EN_PASSANT = -1;


class GameState {
/*============================================================================*/
// PRIVATE MEMBER VARIABLES
private:
    uint64_t m_wpbb, m_bpbb;
    uint64_t m_pbb, m_nbb, m_bbb, m_rbb, m_qbb, m_kbb;
    PlayerColour m_activeColour;
    int m_castlingRights;
    int m_enPassant;
    int m_halfMoveClock;
    int m_fullMoveCount;

/*============================================================================*/
// PUBLIC CALLABLE METHODS  
public:
    GameState(std::string FEN);

    // Create a new Chess game with the starting position
    GameState();
    
    // Return the piece bitboard of the specified colour
    uint64_t pieceBB(Piece piece);

    // Return the empty bitboard
    uint64_t getEmptyBB();

    // Return the currently active colour
    PlayerColour getActiveColour();

    // given a square (0-63), return the piece at that square
    Piece getPieceAtSquare(int square);

    // Return the en passant square
    int getEnPassant();
/*============================================================================*/
// PRIVATE HELPER METHODS
private: 
    char getPieceChar(Piece);

};

#endif
