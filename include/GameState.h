#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <string>

#include <limits>
#include "BoardConstants.h"

class GameState {
/*============================================================================*/
// PRIVATE MEMBER VARIABLES
private:
    uint64_t m_bboards[BB_COUNT];
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

    // return the bitboards for reading only
    const uint64_t* getPosBB();

    // Return the pawn bitboard for reading
    uint64_t getPawnBB(PlayerColour colour);

    // Return the empty bitboard
    uint64_t getEmptyBB();

    // Return the currently active colour
    PlayerColour getActiveColour();

    // Print the GameState
    void PrintGameState();

/*============================================================================*/
// PRIVATE HELPER METHODS
private: 
    char getPieceChar(bbVal Piece);

    bbVal getPieceAtSquare(int square);
};

#endif
